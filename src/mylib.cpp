#include "mylib.hpp"

#include <cctype>

std::string make_greeting(std::string_view name) {
    if (name.empty()) {
        name = "World";
    } else {
        while (!name.empty() && std::isspace(static_cast<unsigned char>(name.front()))) {
            name.remove_prefix(1);
        }
        while (!name.empty() && std::isspace(static_cast<unsigned char>(name.back()))) {
            name.remove_suffix(1);
        }
        if (name.empty()) {
            name = "World";
        }
    }
    return "Hello, " + std::string{name} + "!";
}
