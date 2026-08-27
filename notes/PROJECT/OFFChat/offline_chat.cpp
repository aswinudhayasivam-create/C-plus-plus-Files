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
#include <sodium.h>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

struct Message {
    std::string id;
    std::string from;
    std::string to;        // empty = broadcast
    std::string content;
    std::string timestamp;
};

class Encryptor {
    unsigned char key[crypto_aead_aes256gcm_KEYBYTES];
public:
    Encryptor(const std::string& password) {
        if (sodium_init() < 0) {
            throw std::runtime_error("Failed to initialize libsodium");
        }
        // Simple key derivation (for demo). In production use Argon2id
        crypto_generichash(key, sizeof(key),
                          reinterpret_cast<const unsigned char*>(password.data()),
                          password.size(), nullptr, 0);
    }

    std::vector<uint8_t> encrypt(const std::string& plaintext) {
        std::vector<uint8_t> ciphertext(plaintext.size() + crypto_aead_aes256gcm_ABYTES + crypto_aead_aes256gcm_NPUBBYTES);
        unsigned char nonce[crypto_aead_aes256gcm_NPUBBYTES];
        randombytes_buf(nonce, sizeof(nonce));

        unsigned long long clen;
        crypto_aead_aes256gcm_encrypt(ciphertext.data() + crypto_aead_aes256gcm_NPUBBYTES, &clen,
                                     reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.size(),
                                     nullptr, 0, nullptr, nonce, key);

        std::memcpy(ciphertext.data(), nonce, crypto_aead_aes256gcm_NPUBBYTES);
        ciphertext.resize(crypto_aead_aes256gcm_NPUBBYTES + clen);
        return ciphertext;
    }

    std::string decrypt(const std::vector<uint8_t>& ciphertext) {
        if (ciphertext.size() < crypto_aead_aes256gcm_NPUBBYTES + crypto_aead_aes256gcm_ABYTES) {
            throw std::runtime_error("Invalid ciphertext");
        }
        std::vector<uint8_t> plaintext(ciphertext.size() - crypto_aead_aes256gcm_NPUBBYTES - crypto_aead_aes256gcm_ABYTES);
        unsigned long long mlen;

        if (crypto_aead_aes256gcm_decrypt(plaintext.data(), &mlen, nullptr,
                                         ciphertext.data() + crypto_aead_aes256gcm_NPUBBYTES,
                                         ciphertext.size() - crypto_aead_aes256gcm_NPUBBYTES,
                                         nullptr, 0,
                                         ciphertext.data(), key) != 0) {
            throw std::runtime_error("Decryption failed - wrong key?");
        }
        return std::string(plaintext.begin(), plaintext.begin() + mlen);
    }
};

class OfflineChat {
    std::string username;
    fs::path shared_path;
    fs::path messages_dir;
    Encryptor encryptor;
    std::unordered_set<std::string> seen_ids;
    std::deque<Message> outgoing_queue;
    std::mutex queue_mutex;
    std::atomic<bool> running{true};
    std::thread writer_thread;

    std::string generate_id() {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1000, 9999);
        return std::to_string(ms) + "_" + std::to_string(dis(gen));
    }

    std::string get_timestamp() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::ostringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    void save_message(const Message& msg) {
        json j;
        j["id"] = msg.id;
        j["from"] = msg.from;
        j["to"] = msg.to;
        j["content"] = msg.content;
        j["timestamp"] = msg.timestamp;

        std::string plaintext = j.dump();
        auto encrypted = encryptor.encrypt(plaintext);

        std::string filename = "msg_" + msg.id + ".enc";
        fs::path filepath = messages_dir / filename;

        // Atomic write
        fs::path temp = filepath.string() + ".tmp";
        std::ofstream out(temp, std::ios::binary);
        out.write(reinterpret_cast<const char*>(encrypted.data()), encrypted.size());
        out.close();
        fs::rename(temp, filepath);
    }

    void writer_loop() {
        while (running) {
            std::deque<Message> to_send;
            {
                std::lock_guard<std::mutex> lock(queue_mutex);
                if (!outgoing_queue.empty()) {
                    to_send.swap(outgoing_queue);
                }
            }

            for (const auto& msg : to_send) {
                try {
                    save_message(msg);
                } catch (...) {
                    std::cerr << "Failed to save message\n";
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
        }
    }

    std::vector<Message> scan_new_messages() {
        std::vector<Message> new_msgs;
        if (!fs::exists(messages_dir)) return new_msgs;

        for (const auto& entry : fs::directory_iterator(messages_dir)) {
            if (!entry.is_regular_file() || entry.path().extension() != ".enc") continue;

            std::string filename = entry.path().filename().string();
            if (seen_ids.count(filename)) continue;

            try {
                std::ifstream in(entry.path(), std::ios::binary | std::ios::ate);
                if (!in) continue;
                size_t size = in.tellg();
                in.seekg(0);
                std::vector<uint8_t> data(size);
                in.read(reinterpret_cast<char*>(data.data()), size);

                std::string plaintext = encryptor.decrypt(data);
                json j = json::parse(plaintext);

                Message msg{
                    j["id"], j["from"], j["to"], j["content"], j["timestamp"]
                };

                if (msg.from != username && (msg.to.empty() || msg.to == username)) {
                    new_msgs.push_back(msg);
                    seen_ids.insert(filename);
                } else {
                    seen_ids.insert(filename); // still mark as seen
                }
            } catch (...) {
                // silent fail on bad messages
            }
        }
        return new_msgs;
    }

public:
    OfflineChat(const std::string& user, const std::string& path, const std::string& password)
        : username(user), shared_path(path), encryptor(password) {
        messages_dir = shared_path / "messages";
        fs::create_directories(messages_dir);

        writer_thread = std::thread(&OfflineChat::writer_loop, this);
        std::cout << "Offline Chat started as " << username << "\n";
        std::cout << "Shared folder: " << shared_path << "\n";
        std::cout << "Type messages or /to <username> <message>\n";
        std::cout << "Commands: /quit, /help\n\n";
    }

    ~OfflineChat() {
        running = false;
        if (writer_thread.joinable()) writer_thread.join();
    }

    void enqueue_message(const std::string& content, const std::string& to = "") {
        Message msg{
            generate_id(), username, to, content, get_timestamp()
        };
        std::lock_guard<std::mutex> lock(queue_mutex);
        outgoing_queue.push_back(std::move(msg));
    }

    void run() {
        std::string line;
        auto last_scan = std::chrono::steady_clock::now();

        while (running) {
            // Check for new messages every ~1.5 seconds
            auto now = std::chrono::steady_clock::now();
            if (now - last_scan > std::chrono::milliseconds(1500)) {
                auto new_msgs = scan_new_messages();
                for (const auto& msg : new_msgs) {
                    std::cout << "\n[" << msg.timestamp << "] ";
                    if (!msg.to.empty()) std::cout << "(Private) ";
                    std::cout << msg.from << ": " << msg.content << "\n> ";
                    std::cout.flush();
                }
                last_scan = now;
            }

            // Non-blocking input simulation (simple getline with timeout not used for simplicity)
            if (std::cin.peek() != EOF) {
                std::getline(std::cin, line);
                if (line.empty()) continue;

                if (line == "/quit") break;
                if (line == "/help") {
                    std::cout << "Just type to broadcast\n/to <user> <msg> for private\n/quit to exit\n";
                    continue;
                }

                if (line.rfind("/to ", 0) == 0) {
                    size_t space2 = line.find(' ', 4);
                    if (space2 != std::string::npos) {
                        std::string to_user = line.substr(4, space2 - 4);
                        std::string msg_text = line.substr(space2 + 1);
                        enqueue_message(msg_text, to_user);
                        std::cout << "→ Sent to " << to_user << "\n";
                    }
                } else {
                    enqueue_message(line);
                    std::cout << "→ Broadcast sent\n";
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};

int main(int argc, char* argv[]) {
    std::string username = "User";
    std::string shared_path = "./shared_chat";
    std::string password = "offlinechat123";   // Change this! All users must use same password

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--username" && i + 1 < argc) username = argv[++i];
        else if (arg == "--path" && i + 1 < argc) shared_path = argv[++i];
        else if (arg == "--password" && i + 1 < argc) password = argv[++i];
    }

    try {
        OfflineChat app(username, shared_path, password);
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nGoodbye!\n";
    return 0;
}