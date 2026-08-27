#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <random>
#include <ctime>

namespace fs = std::filesystem;

class VirtualAssistant; // Forward declaration for Command::execute

class Command {
public:
    virtual ~Command() = default;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual void execute(VirtualAssistant& assistant, const std::vector<std::string>& args) = 0;
};

class CommandRegistry {
private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands;
public:
    void registerCommand(std::unique_ptr<Command> cmd) {
        std::string name = cmd->getName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        commands[name] = std::move(cmd);
    }

    Command* getCommand(const std::string& name) {
        auto it = commands.find(name);
        return (it != commands.end()) ? it->second.get() : nullptr;
    }

    void listCommands() const {
        std::cout << "Available commands:\n";
        for (const auto& pair : commands) {
            std::cout << "  " << pair.first << " - " << pair.second->getDescription() << "\n";
        }
    }
};

class InputParser {
public:
    std::vector<std::string> parse(const std::string& input) {
        std::vector<std::string> tokens;
        std::istringstream iss(input);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }
};

class FileManager {
private:
    fs::path currentDir;
public:
    FileManager() : currentDir(fs::current_path()) {}

    const fs::path& getCurrentDir() const { return currentDir; }

    void setCurrentDir(const std::string& dirName) {
        fs::path newDir = currentDir / dirName;
        if (fs::is_directory(newDir)) {
            currentDir = newDir;
            std::cout << "Changed directory to: " << currentDir << "\n";
        } else {
            std::cout << "Directory not found.\n";
        }
    }

    void listFiles() const {
        std::cout << "Contents of " << currentDir << ":\n";
        for (const auto& entry : fs::directory_iterator(currentDir)) {
            std::cout << "  " << entry.path().filename().string();
            if (entry.is_directory()) std::cout << "/";
            std::cout << "\n";
        }
    }

    void createDirectory(const std::string& name) {
        fs::path p = currentDir / name;
        if (fs::create_directory(p)) std::cout << "Directory created: " << name << "\n";
        else std::cout << "Failed to create directory.\n";
    }

    void createFile(const std::string& name) {
        std::ofstream ofs(currentDir / name);
        if (ofs) std::cout << "File created: " << name << "\n";
        else std::cout << "Failed to create file.\n";
    }

    void readFile(const std::string& name) {
        std::ifstream ifs(currentDir / name);
        if (ifs) {
            std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            std::cout << content << "\n";
        } else {
            std::cout << "File not found or cannot be read.\n";
        }
    }

    void writeFile(const std::string& name, const std::string& content) {
        std::ofstream ofs(currentDir / name);
        if (ofs) {
            ofs << content;
            std::cout << "Written to file: " << name << "\n";
        } else {
            std::cout << "Failed to write to file.\n";
        }
    }

    void deleteFile(const std::string& name) {
        fs::path p = currentDir / name;
        if (fs::remove(p)) std::cout << "Deleted: " << name << "\n";
        else std::cout << "Failed to delete (file may not exist).\n";
    }
};

class AIResponder {
private:
    std::vector<std::string> jokes = {
        "Why do programmers prefer dark mode? Because light attracts bugs!",
        "How many programmers does it take to change a light bulb? None – that's a hardware problem.",
        "Why was the JavaScript developer sad? He didn't know how to 'null' his feelings."
    };
    std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<> dis{0, 2};

public:
    void respond(const std::string& query) {
        std::string lower = query;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        if (lower.find("hello") != std::string::npos || lower.find("hi") != std::string::npos) {
            std::cout << "Hello, sir. How can I assist you today?\n";
        } else if (lower.find("how are you") != std::string::npos) {
            std::cout << "I'm operating at 100% efficiency, sir!\n";
        } else if (lower.find("time") != std::string::npos || lower.find("what time") != std::string::npos) {
            auto now = std::chrono::system_clock::now();
            auto t = std::chrono::system_clock::to_time_t(now);
            std::cout << "Current time: " << std::put_time(std::localtime(&t), "%H:%M:%S") << "\n";
        } else if (lower.find("date") != std::string::npos) {
            auto now = std::chrono::system_clock::now();
            auto t = std::chrono::system_clock::to_time_t(now);
            std::cout << "Today's date: " << std::put_time(std::localtime(&t), "%Y-%m-%d") << "\n";
        } else if (lower.find("joke") != std::string::npos) {
            std::cout << jokes[dis(gen)] << "\n";
        } else {
            std::cout << "I'm sorry, sir. I didn't quite catch that. Try 'help' for available commands.\n";
        }
    }
};

class VirtualAssistant {
private:
    CommandRegistry registry;
    InputParser parser;
    FileManager fileManager;
    AIResponder aiResponder;
    bool running = true;

public:
    void initCommands() {
        // Built-in commands (core features)
        registry.registerCommand(std::make_unique<class HelpCommand>());
        registry.registerCommand(std::make_unique<class QuitCommand>());
        registry.registerCommand(std::make_unique<class HelloCommand>());
        registry.registerCommand(std::make_unique<class TimeCommand>());
        registry.registerCommand(std::make_unique<class ListFilesCommand>());
        registry.registerCommand(std::make_unique<class MkdirCommand>());
        registry.registerCommand(std::make_unique<class TouchCommand>());
        registry.registerCommand(std::make_unique<class ReadCommand>());
        registry.registerCommand(std::make_unique<class WriteCommand>());
        registry.registerCommand(std::make_unique<class DeleteCommand>());
        registry.registerCommand(std::make_unique<class CdCommand>());

        // Plugin example area - add new commands here for extensibility
        // Example: registry.registerCommand(std::make_unique<YourCustomPluginCommand>());
    }

    void registerCommand(std::unique_ptr<Command> cmd) {
        registry.registerCommand(std::move(cmd));
    }

    void run() {
        std::cout << "========================================\n";
        std::cout << "Jarvis at your service, sir!\n";
        std::cout << "Type 'help' for commands. Say 'quit' to exit.\n";
        std::cout << "========================================\n";

        std::string input;
        while (running) {
            std::cout << "\nJarvis> ";
            std::getline(std::cin, input);
            if (input.empty()) continue;

            // Optional: strip leading "jarvis " prefix for natural feel
            if (input.size() >= 7 && input.substr(0, 7) == "jarvis ") {
                input = input.substr(7);
            }

            auto tokens = parser.parse(input);
            if (tokens.empty()) continue;

            std::string cmdStr = tokens[0];
            std::transform(cmdStr.begin(), cmdStr.end(), cmdStr.begin(), ::tolower);
            std::vector<std::string> args(tokens.begin() + 1, tokens.end());

            Command* cmd = registry.getCommand(cmdStr);
            if (cmd) {
                cmd->execute(*this, args);
            } else {
                aiResponder.respond(input);  // Basic AI fallback
            }
        }
    }

    FileManager& getFileManager() { return fileManager; }
    void quit() { running = false; }
    void listCommands() { registry.listCommands(); }
};

// ==================== Concrete Commands (Plugins) ====================

class HelpCommand : public Command {
public:
    std::string getName() const override { return "help"; }
    std::string getDescription() const override { return "Show all available commands"; }
    void execute(VirtualAssistant& assistant, const std::vector<std::string>& args) override {
        assistant.listCommands();
    }
};

class QuitCommand : public Command {
public:
    std::string getName() const override { return "quit"; }
    std::string getDescription() const override { return "Exit Jarvis"; }
    void execute(VirtualAssistant& assistant, const std::vector<std::string>& args) override {
        std::cout << "Goodbye, sir. Shutting down...\n";
        assistant.quit();
    }
};

class HelloCommand : public Command {
public:
    std::string getName() const override { return "hello"; }
    std::string getDescription() const override { return "Greet Jarvis"; }
    void execute(VirtualAssistant& assistant, const std::vector<std::string>& args) override {
        std::cout << "Hello, sir. Always at your service!\n";
    }
};

class TimeCommand : public Command {
public:
    std::string getName() const override { return "time"; }
    std::string getDescription() const override { return "Show current time"; }
    void execute(VirtualAssistant& assistant, const std::vector<std::string>& args) override {
        auto now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);
        std::cout << "Current time: " << std::put_time(std::localtime(&t), "%H:%M:%S") << "\n";
    }
};

class ListFilesCommand : public Command {
public:
    std::string getName() const override { return "ls"; }
    std::string getDescription() const override { return "List files in current directory"; }
    void execute(VirtualAssistant& assistant, const std::vector<std::string>& args) override {
        assistant.getFileManager().listFiles();
    }
};

class MkdirCommand : public Command {
public:
    std::string getName() const override { return "mkdir"; }
    std::string getDescription() const override { return "Create a new directory (mkdir <name>)"; }
    void execute(VirtualAssistant& assistant, const std::vector<std::string>& args) override {
        if (args.empty()) { std::cout << "Usage: mkdir <dirname>\n"; return; }
        assistant.getFileManager().createDirectory(args[0]);
    }
};

class TouchCommand : public Command {
public:
    std::string getName() const override { return "touch"; }
    std::string getDescription() const override { return "Create a new empty file (touch <filename>)"; }
    void execute(VirtualAssistant& assistant, const std::vector<std::string>& args) override {
        if (args.empty()) { std::cout << "Usage: touch <filename>\n"; return; }
        assistant.getFileManager().createFile(args[0]);
    }
};

class ReadCommand : public Command {
public:
    std::string getName() const override { return "read"; }
    std::string getDescription() const override { return "Read file contents (read <filename>)"; }
    void execute(VirtualAssistant& assistant, const std::vector<std::string>& args) override {
        if (args.empty()) { std::cout << "Usage: read <filename>\n"; return; }
        assistant.getFileManager().readFile(args[0]);
    }
};

class WriteCommand : public Command {
public:
    std::string getName() const override { return "write"; }
    std::string getDescription() const override { return "Write text to file (write <filename> <text...>)"; }
    void execute(VirtualAssistant& assistant, const std::vector<std::string>& args) override {
        if (args.empty()) { std::cout << "Usage: write <filename> <content...>\n"; return; }
        std::string filename = args[0];
        std::string content;
        for (size_t i = 1; i < args.size(); ++i) {
            if (i > 1) content += " ";
            content += args[i];
        }
        assistant.getFileManager().writeFile(filename, content);
    }
};

class DeleteCommand : public Command {
public:
    std::string getName() const override { return "rm"; }
    std::string getDescription() const override { return "Delete a file (rm <filename>)"; }
    void execute(VirtualAssistant& assistant, const std::vector<std::string>& args) override {
        if (args.empty()) { std::cout << "Usage: rm <filename>\n"; return; }
        assistant.getFileManager().deleteFile(args[0]);
    }
};

class CdCommand : public Command {
public:
    std::string getName() const override { return "cd"; }
    std::string getDescription() const override { return "Change directory (cd <dirname>)"; }
    void execute(VirtualAssistant& assistant, const std::vector<std::string>& args) override {
        if (args.empty()) { std::cout << "Usage: cd <dirname>\n"; return; }
        assistant.getFileManager().setCurrentDir(args[0]);
    }
};

// ==================== Main Entry Point ====================
int main() {
    VirtualAssistant jarvis;
    jarvis.initCommands();
    jarvis.run();
    return 0;
}