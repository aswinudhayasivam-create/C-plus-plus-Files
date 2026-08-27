#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
namespace fs = std::filesystem;

mutex fileMutex;
mutex coutMutex;
set<string> seenMessages;

class Utils {
public:
    static string getTime() {
        return to_string(time(0));
    }

    static string generateID() {
        return to_string(time(0)) + "_" + to_string(rand() % 100000);
    }

    static string hashPassword(const string &pass) {
        return to_string(hash<string>{}(pass));
    }
};

class EncryptionService {
public:
    static string process(string msg, string key) {
        for (int i = 0; i < msg.size(); i++)
            msg[i] ^= key[i % key.size()];
        return msg;
    }
};

class Message {
public:
    string id, sender, receiver, content, timestamp;

    Message() {}

    Message(string s, string r, string c) {
        id = Utils::generateID();
        sender = s;
        receiver = r;
        content = c;
        timestamp = Utils::getTime();
    }

    string serialize() {
        return id + "|" + sender + "|" + receiver + "|" +
               content + "|" + timestamp;
    }

    static Message deserialize(const string &data) {
        Message msg;
        vector<string> parts;
        string temp;

        for (char c : data) {
            if (c == '|') {
                parts.push_back(temp);
                temp.clear();
            } else temp += c;
        }
        parts.push_back(temp);

        if (parts.size() >= 5) {
            msg.id = parts[0];
            msg.sender = parts[1];
            msg.receiver = parts[2];
            msg.content = parts[3];
            msg.timestamp = parts[4];
        }
        return msg;
    }
};

class FileService {
public:
    static void writeFile(const string &path, const string &content) {
        lock_guard<mutex> lock(fileMutex);
        ofstream file(path);
        file << content;
    }

    static vector<string> listUsers() {
        vector<string> users;
        string path = "data/users/";
        if (!fs::exists(path)) return users;

        for (auto &p : fs::directory_iterator(path))
            users.push_back(p.path().stem().string());

        return users;
    }

    static vector<pair<string,string>> readNewFiles(const string &folder) {
        vector<pair<string,string>> data;

        if (!fs::exists(folder)) return data;

        for (auto &p : fs::directory_iterator(folder)) {
            string filepath = p.path().string();

            if (seenMessages.count(filepath)) continue;

            seenMessages.insert(filepath);

            ifstream file(filepath);
            string line;
            getline(file, line);

            data.push_back({filepath, line});
        }
        return data;
    }
};

class AuthService {
public:
    static void signup() {
        string user, pass;
        cin >> user >> pass;

        fs::create_directories("data/users");

        string path = "data/users/" + user + ".txt";

        if (fs::exists(path)) {
            cout << "User exists\n";
            return;
        }

        FileService::writeFile(path, user + "|" + Utils::hashPassword(pass));
        cout << "Signup success\n";
    }

    static string login() {
        string user, pass;
        cin >> user >> pass;

        string path = "data/users/" + user + ".txt";

        if (!fs::exists(path)) return "";

        ifstream file(path);
        string data;
        getline(file, data);

        int pos = data.find('|');
        if (pos == string::npos) return "";

        string stored = data.substr(pos + 1);

        if (stored == Utils::hashPassword(pass))
            return user;

        return "";
    }
};

class ChatService {
public:
    static string KEY;

    static string path(string a, string b) {
        string p = "data/chats/" + a + "_" + b + "/";
        fs::create_directories(p);
        return p;
    }

    static void send(string from, string to, string msg) {
        if (from == to) return;

        string enc = EncryptionService::process(msg, KEY);
        Message m(from, to, enc);

        string filepath = path(from, to) + m.id + ".txt";
        FileService::writeFile(filepath, m.serialize());
    }

    static void listener(string user) {
        while (true) {
            this_thread::sleep_for(chrono::seconds(1));

            string base = "data/chats/";
            if (!fs::exists(base)) continue;

            for (auto &dir : fs::directory_iterator(base)) {
                string folder = dir.path().filename().string();

                if (folder.find("_" + user) == string::npos) continue;

                string fullPath = base + folder + "/";

                auto msgs = FileService::readNewFiles(fullPath);

                for (auto &p : msgs) {
                    Message m = Message::deserialize(p.second);
                    string text = EncryptionService::process(m.content, KEY);

                    lock_guard<mutex> lock(coutMutex);
                    cout << "\n[" << m.sender << "] " << text << "\n> ";
                }
            }
        }
    }
};

string ChatService::KEY = "GROUP_SECRET_KEY";

int main() {
    srand(time(0));

    fs::create_directories("data/chats");
    fs::create_directories("data/users");

    string user;

    cout << "1 Signup 2 Login\n";
    int c;
    cin >> c;

    if (c == 1) AuthService::signup();

    cout << "Login:\n";
    user = AuthService::login();

    if (user == "") return 0;

    thread t(ChatService::listener, user);
    t.detach();

    while (true) {
        auto users = FileService::listUsers();

        cout << "\nUsers:\n";
        for (int i = 0; i < users.size(); i++)
            if (users[i] != user)
                cout << i+1 << ". " << users[i] << endl;

        if (users.empty()) {
            cout << "No users available\n";
            continue;
        }

        int choice;
        cin >> choice;

        if (choice < 1 || choice > users.size()) continue;

        string to = users[choice - 1];

        cin.ignore();
        string msg;
        getline(cin, msg);

        ChatService::send(user, to, msg);
    }
}