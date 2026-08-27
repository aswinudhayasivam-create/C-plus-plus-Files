#include <bits/stdc++.h>
#include <filesystem>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;
namespace fs = std::filesystem;

/* ===================== UTILS ===================== */
class Utils {
public:
    static string getTime() {
        time_t now = time(0);
        return to_string(now);
    }

    static string generateID() {
        return to_string(rand() % 1000000000);
    }

    static string hashPassword(string pass) {
        int hash = 0;
        for (char c : pass)
            hash = (hash * 31 + c) % 1000000007;
        return to_string(hash);
    }
};

/* ===================== ENCRYPTION ===================== */
class EncryptionService {
public:
    static string encrypt(string msg, string key) {
        for (int i = 0; i < msg.size(); i++)
            msg[i] ^= key[i % key.size()];
        return msg;
    }

    static string decrypt(string msg, string key) {
        return encrypt(msg, key);
    }
};

/* ===================== MESSAGE ===================== */
class Message {
public:
    string id, sender, receiver, content, timestamp, status;

    Message() {}

    Message(string i, string s, string r, string c, string t) {
        id = i;
        sender = s;
        receiver = r;
        content = c;
        timestamp = t;
        status = "sent";
    }

    string serialize() {
        return id + "|" + sender + "|" + receiver + "|" +
               content + "|" + timestamp + "|" + status;
    }

    static Message deserialize(string data) {
        Message msg;
        string parts[6];
        int j = 0;
        for (char c : data) {
            if (c == '|') j++;
            else parts[j] += c;
        }
        msg.id = parts[0];
        msg.sender = parts[1];
        msg.receiver = parts[2];
        msg.content = parts[3];
        msg.timestamp = parts[4];
        msg.status = parts[5];
        return msg;
    }
};

/* ===================== FILE SERVICE ===================== */
class FileService {
public:
    static void writeFile(string path, string content) {
        ofstream file(path);
        file << content;
        file.close();
    }

    static vector<string> readAllFiles(string folder) {
        vector<string> data;
        for (auto &p : fs::directory_iterator(folder)) {
            ifstream file(p.path());
            string line;
            getline(file, line);
            data.push_back(line);
        }
        return data;
    }
};

/* ===================== AUTH ===================== */
class AuthService {
public:
    static void signup() {
        string user, pass;
        cout << "New Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;

        fs::create_directories("data/users");

        string path = "data/users/" + user + ".txt";

        if (fs::exists(path)) {
            cout << "User already exists!\n";
            return;
        }

        ofstream file(path);
        file << user << "|" << Utils::hashPassword(pass);
        file.close();

        cout << "✅ User created!\n";
    }

    static string login() {
        string user, pass;
        cout << "Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;

        string path = "data/users/" + user + ".txt";

        if (!fs::exists(path)) {
            cout << "User not found!\n";
            return "";
        }

        ifstream file(path);
        string data;
        getline(file, data);

        int pos = data.find('|');
        string storedPass = data.substr(pos + 1);

        if (Utils::hashPassword(pass) == storedPass) {
            cout << "✅ Login successful!\n";
            return user;
        }

        cout << "❌ Wrong password!\n";
        return "";
    }
};

/* ===================== CHAT MANAGER ===================== */
class ChatManager {
public:
    static string KEY;

    static string getPath(string a, string b) {
        string path = "data/chats/" + a + "_" + b + "/";
        fs::create_directories(path);
        return path;
    }

    static void sendMessage(string sender, string receiver, string msg) {
        string encrypted = EncryptionService::encrypt(msg, KEY);

        Message m(Utils::generateID(), sender, receiver, encrypted, Utils::getTime());

        string path = getPath(sender, receiver);
        FileService::writeFile(path + m.id + ".txt", m.serialize());

        cout << "📤 Sent!\n";
    }

    static void receiveMessages(string user, string from) {
        string path = "data/chats/" + from + "_" + user + "/";

        if (!fs::exists(path)) {
            cout << "No messages.\n";
            return;
        }

        auto msgs = FileService::readAllFiles(path);

        for (auto &m : msgs) {
            Message msg = Message::deserialize(m);
            string text = EncryptionService::decrypt(msg.content, KEY);

            cout << "[" << msg.sender << "] " << text << endl;
        }
    }

    static void groupMessage(string sender, vector<string> members, string msg) {
        for (auto &m : members) {
            if (m != sender)
                sendMessage(sender, m, msg);
        }
    }

    static void realTimeListener(string user) {
        while (true) {
            this_thread::sleep_for(chrono::seconds(5));
            cout << "\n🔔 Checking for new messages...\n";
        }
    }
};

string ChatManager::KEY = "phantomkey";

/* ===================== MAIN ===================== */
int main() {
    srand(time(0));

    fs::create_directories("data/chats");
    fs::create_directories("data/users");

    string currentUser = "";

    cout << "===== PHANTOMLINK =====\n";

    while (true) {
        cout << "\n1. Signup\n2. Login\n3. Exit\nChoice: ";
        int c;
        cin >> c;

        if (c == 1) AuthService::signup();
        else if (c == 2) {
            currentUser = AuthService::login();
            if (currentUser != "") break;
        }
        else return 0;
    }

    thread listener(ChatManager::realTimeListener, currentUser);
    listener.detach();

    while (true) {
        cout << "\n==== MENU ====\n";
        cout << "1. Send Message\n2. Read Messages\n3. Group Message\n4. Exit\nChoice: ";

        int ch;
        cin >> ch;

        if (ch == 1) {
            string to, msg;
            cout << "To: ";
            cin >> to;
            cin.ignore();
            cout << "Message: ";
            getline(cin, msg);

            ChatManager::sendMessage(currentUser, to, msg);
        }
        else if (ch == 2) {
            string from;
            cout << "From: ";
            cin >> from;

            ChatManager::receiveMessages(currentUser, from);
        }
        else if (ch == 3) {
            int n;
            cout << "Members count: ";
            cin >> n;

            vector<string> members(n);
            for (int i = 0; i < n; i++) cin >> members[i];

            cin.ignore();
            string msg;
            cout << "Message: ";
            getline(cin, msg);

            ChatManager::groupMessage(currentUser, members, msg);
        }
        else break;
    }

    return 0;
}