#include "mylib.hpp"

std::string make_greeting(std::string_view name) {
    if (name.empty()) {
        name = "World";
    }
    return "Hello, " + std::string{name} + "!";
}
