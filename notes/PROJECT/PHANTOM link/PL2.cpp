#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <unordered_set>
#include <deque>
#include <random>
#include <cstring>

#include <sodium.h>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

// ================= MESSAGE =================
struct Message {
    std::string id, from, to, type, content, timestamp;
};

// ================= ENCRYPTOR =================
class Encryptor {
    unsigned char key[crypto_aead_chacha20poly1305_ietf_KEYBYTES];

public:
    Encryptor(const std::string& password) {
        if (sodium_init() < 0)
            throw std::runtime_error("libsodium init failed");

        crypto_generichash(key, sizeof(key),
            (const unsigned char*)password.data(),
            password.size(), nullptr, 0);
    }

    std::vector<uint8_t> encrypt(const std::string& plaintext) {
        unsigned char nonce[crypto_aead_chacha20poly1305_ietf_NPUBBYTES];
        randombytes_buf(nonce, sizeof(nonce));

        std::vector<uint8_t> cipher(
            plaintext.size() +
            crypto_aead_chacha20poly1305_ietf_ABYTES +
            sizeof(nonce));

        unsigned long long clen;

        crypto_aead_chacha20poly1305_ietf_encrypt(
            cipher.data() + sizeof(nonce), &clen,
            (const unsigned char*)plaintext.data(),
            plaintext.size(),
            nullptr, 0, nullptr,
            nonce, key
        );

        std::memcpy(cipher.data(), nonce, sizeof(nonce));
        cipher.resize(sizeof(nonce) + clen);
        return cipher;
    }

    std::string decrypt(const std::vector<uint8_t>& cipher) {
        if (cipher.size() < crypto_aead_chacha20poly1305_ietf_NPUBBYTES)
            throw std::runtime_error("Invalid cipher");

        const unsigned char* nonce = cipher.data();

        std::vector<uint8_t> plain(cipher.size());
        unsigned long long plen;

        if (crypto_aead_chacha20poly1305_ietf_decrypt(
            plain.data(), &plen, nullptr,
            cipher.data() + crypto_aead_chacha20poly1305_ietf_NPUBBYTES,
            cipher.size() - crypto_aead_chacha20poly1305_ietf_NPUBBYTES,
            nullptr, 0,
            nonce, key) != 0)
        {
            throw std::runtime_error("Decrypt failed");
        }

        return std::string(plain.begin(), plain.begin() + plen);
    }
};

// ================= CHAT =================
class ChatSystem {
    std::string username;
    fs::path base, msg_dir, user_dir, group_dir;
    Encryptor encryptor;

    std::unordered_set<std::string> seen;
    std::unordered_set<std::string> my_groups;

    std::mutex mtx;
    std::deque<Message> queue;

    std::atomic<bool> running{true};
    std::thread writer;

    // ---------- utils ----------
    std::string now() {
        auto t = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
        std::stringstream ss;
        ss << std::put_time(std::localtime(&t), "%H:%M:%S");
        return ss.str();
    }

    std::string id() {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(100000, 999999);

        auto t = std::chrono::system_clock::now().time_since_epoch().count();
        return std::to_string(t) + "_" + std::to_string(dist(rng));
    }

    // ---------- presence ----------
    void update_presence() {
        std::ofstream f(user_dir / (username + ".usr"));
        f << std::time(nullptr);
    }

    std::vector<std::string> get_users() {
        std::vector<std::string> users;
        auto now = std::time(nullptr);

        for (auto& f : fs::directory_iterator(user_dir)) {
            std::ifstream in(f.path());
            time_t t; in >> t;

            if (now - t < 5)
                users.push_back(f.path().stem().string());
        }
        return users;
    }

    // ---------- groups ----------
    void load_groups() {
        fs::create_directories(group_dir);

        for (auto& f : fs::directory_iterator(group_dir)) {
            std::ifstream in(f.path());
            json j; in >> j;

            for (auto& u : j["members"])
                if (u == username)
                    my_groups.insert(f.path().stem().string());
        }
    }

    void create_group(std::string name, std::vector<std::string> members) {
        json j;
        j["members"] = members;

        std::ofstream(group_dir / (name + ".json")) << j.dump(2);
        std::cout << "Group created\n";
    }

    // ---------- writer ----------
    void writer_loop() {
        while (running) {
            std::deque<Message> temp;

            {
                std::lock_guard<std::mutex> lock(mtx);
                temp.swap(queue);
            }

            for (auto& m : temp) save(m);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    void save(const Message& m) {
        json j = {
            {"id", m.id},
            {"from", m.from},
            {"to", m.to},
            {"type", m.type},
            {"content", m.content},
            {"time", m.timestamp}
        };

        auto enc = encryptor.encrypt(j.dump());

        auto temp = msg_dir / ("tmp_" + m.id);
        auto final = msg_dir / ("msg_" + m.id + ".enc");

        std::ofstream f(temp, std::ios::binary);
        f.write((char*)enc.data(), enc.size());
        f.close();

        fs::rename(temp, final);
    }

    // ---------- read ----------
    void read_messages() {
        for (auto& f : fs::directory_iterator(msg_dir)) {
            auto name = f.path().filename().string();
            if (seen.count(name)) continue;

            try {
                std::ifstream in(f.path(), std::ios::binary | std::ios::ate);
                std::streamsize size = in.tellg();
                if (size <= 0) continue;

                in.seekg(0);
                std::vector<uint8_t> data(size);
                in.read((char*)data.data(), size);

                auto text = encryptor.decrypt(data);
                auto j = json::parse(text);

                Message m{
                    j.value("id",""), j.value("from",""),
                    j.value("to",""), j.value("type",""),
                    j.value("content",""), j.value("time","")
                };

                bool show = false;

                if (m.type == "broadcast") show = true;
                else if (m.type == "private" && m.to == username) show = true;
                else if (m.type == "group" && my_groups.count(m.to)) show = true;

                if (m.from != username && show) {
                    std::cout << "\n[" << m.timestamp << "] "
                              << m.from << " → " << m.to
                              << " : " << m.content << "\n> ";
                }

                seen.insert(name);

            } catch (const std::exception& e) {
                std::cerr << "Read error: " << e.what() << "\n";
            }
        }
    }

public:
    ChatSystem(std::string user, std::string path, std::string pass)
        : username(user), base(path), encryptor(pass)
    {
        msg_dir = base / "messages";
        user_dir = base / "users";
        group_dir = base / "groups";

        fs::create_directories(msg_dir);
        fs::create_directories(user_dir);
        fs::create_directories(group_dir);

        load_groups();
        writer = std::thread(&ChatSystem::writer_loop, this);
    }

    ~ChatSystem() {
        running = false;
        if (writer.joinable()) writer.join();
    }

    void send(std::string msg, std::string to="", std::string type="broadcast") {
        Message m{ id(), username, to, type, msg, now() };
        std::lock_guard<std::mutex> lock(mtx);
        queue.push_back(m);
    }

    void run() {
        std::string input;

        while (running) {
            update_presence();
            read_messages();

            std::cout << "> ";
            std::getline(std::cin, input);

            if (input == "/quit") {
                running = false;
                break;
            }

            if (input == "/users") {
                for (auto& u : get_users())
                    std::cout << "- " << u << "\n";
                continue;
            }

            if (input.rfind("/groupcreate ", 0) == 0) {
                std::stringstream ss(input.substr(13));
                std::string name, user;
                ss >> name;

                std::vector<std::string> members;
                while (ss >> user) members.push_back(user);

                create_group(name, members);
                load_groups();
                continue;
            }

            if (input.rfind("/to ", 0) == 0) {
                auto pos = input.find(' ', 4);
                if (pos == std::string::npos) continue;

                send(input.substr(pos+1),
                     input.substr(4, pos-4), "private");
                continue;
            }

            if (input.rfind("/group ", 0) == 0) {
                auto pos = input.find(' ', 7);
                if (pos == std::string::npos) continue;

                send(input.substr(pos+1),
                     input.substr(7, pos-7), "group");
                continue;
            }

            send(input);
        }
    }
};

// ================= MAIN =================
int main(int argc, char* argv[]) {
    std::string user = "User";
    std::string path = "./chat";
    std::string pass = "secure123";

    for (int i=1;i<argc;i++) {
        std::string a = argv[i];
        if (a=="--user") user = argv[++i];
        else if (a=="--path") path = argv[++i];
        else if (a=="--pass") pass = argv[++i];
    }

    try {
        ChatSystem app(user, path, pass);
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what();
    }
}