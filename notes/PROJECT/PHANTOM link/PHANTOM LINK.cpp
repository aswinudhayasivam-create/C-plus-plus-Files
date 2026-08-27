#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
namespace fs = std::filesystem;

mutex fileMutex, coutMutex;
set<string> seenMessages;

class Utils {
public:
    static string timeNow() {
        return to_string(time(0));
    }
    static string genID() {
        return to_string(time(0)) + "_" + to_string(rand() % 100000);
    }
};

class Crypto {
public:
    static string process(string msg, string key) {
        for (int i = 0; i < msg.size(); i++)
            msg[i] ^= key[i % key.size()];
        return msg;
    }
};

class Message {
public:
    string id, sender, receiver, content, time;

    Message() {}

    Message(string s, string r, string c) {
        id = Utils::genID();
        sender = s;
        receiver = r;
        content = c;
        time = Utils::timeNow();
    }

    string serialize() {
        return id + "|" + sender + "|" + receiver + "|" + content + "|" + time;
    }

    static Message parse(string data) {
        Message m;
        vector<string> v;
        string t;

        for (char c : data) {
            if (c == '|') {
                v.push_back(t);
                t.clear();
            } else t += c;
        }
        v.push_back(t);

        if (v.size() >= 5) {
            m.id = v[0];
            m.sender = v[1];
            m.receiver = v[2];
            m.content = v[3];
            m.time = v[4];
        }
        return m;
    }
};

class FileService {
public:
    static void write(string path, string data) {
        lock_guard<mutex> lock(fileMutex);
        ofstream f(path);
        f << data;
    }

    static vector<string> getUsers() {
        vector<string> users;
        if (!fs::exists("data/users")) return users;

        for (auto &p : fs::directory_iterator("data/users"))
            users.push_back(p.path().stem().string());

        return users;
    }

    static vector<string> getRecentChats(string user) {
        vector<string> chats;
        if (!fs::exists("data/chats")) return chats;

        for (auto &p : fs::directory_iterator("data/chats")) {
            string folder = p.path().filename().string();

            if (folder.find(user + "_") == 0)
                chats.push_back(folder.substr(user.size() + 1));
            else if (folder.find("_" + user) != string::npos)
                chats.push_back(folder.substr(0, folder.find("_")));
        }

        sort(chats.begin(), chats.end());
        chats.erase(unique(chats.begin(), chats.end()), chats.end());
        return chats;
    }

    static vector<pair<string,string>> readNew(string folder) {
        vector<pair<string,string>> out;

        if (!fs::exists(folder)) return out;

        for (auto &p : fs::directory_iterator(folder)) {
            string file = p.path().string();

            if (seenMessages.count(file)) continue;
            seenMessages.insert(file);

            ifstream f(file);
            string line;
            getline(f, line);

            out.push_back({file, line});
        }
        return out;
    }
};

class Auth {
public:
    static string login() {
        string u;
        cout << "Enter username: ";
        cin >> u;
        return u;
    }
};

class Chat {
public:
    static string KEY;

    static string path(string a, string b) {
        string p = "data/chats/" + a + "_" + b + "/";
        fs::create_directories(p);
        return p;
    }

    static void send(string from, string to, string msg) {
        if (from == to) return;

        string enc = Crypto::process(msg, KEY);
        Message m(from, to, enc);

        string file = path(from, to) + m.id + ".txt";
        FileService::write(file, m.serialize());
    }

    static void listener(string user) {
        while (true) {
            this_thread::sleep_for(chrono::seconds(1));

            if (!fs::exists("data/chats")) continue;

            for (auto &dir : fs::directory_iterator("data/chats")) {
                string folder = dir.path().filename().string();

                if (folder.find("_" + user) == string::npos) continue;

                auto msgs = FileService::readNew("data/chats/" + folder + "/");

                for (auto &p : msgs) {
                    Message m = Message::parse(p.second);
                    string text = Crypto::process(m.content, KEY);

                    lock_guard<mutex> lock(coutMutex);
                    cout << "\n[" << m.sender << "] " << text << "\n> ";
                }
            }
        }
    }
};

string Chat::KEY = "securekey";

/* ================= MAIN ================= */
int main() {
    srand(time(0));

    fs::create_directories("data/chats");
    fs::create_directories("data/users");

    string user = Auth::login();

    thread t(Chat::listener, user);
    t.detach();

    while (true) {
        cout << "\n==== MENU ====\n";
        cout << "1. Show Users\n2. Recent Chats\n3. Send Message\nChoice: ";

        int ch;
        cin >> ch;

        if (ch == 1) {
            auto users = FileService::getUsers();
            cout << "\nUsers:\n";

            int idx = 1;
            for (auto &u : users) {
                if (u == user) continue;
                cout << idx++ << ". " << u << endl;
            }
        }
        else if (ch == 2) {
            auto chats = FileService::getRecentChats(user);
            cout << "\nRecent Chats:\n";

            for (int i = 0; i < chats.size(); i++)
                cout << i+1 << ". " << chats[i] << endl;
        }
        else if (ch == 3) {
            auto users = FileService::getUsers();
            vector<string> valid;

            for (auto &u : users)
                if (u != user)
                    valid.push_back(u);

            if (valid.empty()) {
                cout << "No users available\n";
                continue;
            }

            cout << "\nSelect User:\n";
            for (int i = 0; i < valid.size(); i++)
                cout << i+1 << ". " << valid[i] << endl;

            int c;
            cin >> c;

            if (c < 1 || c > valid.size()) continue;

            string to = valid[c - 1];

            cin.ignore();
            string msg;
            cout << "Message: ";
            getline(cin, msg);

            Chat::send(user, to, msg);
        }
    }
}
