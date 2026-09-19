#include "mylib.hpp"

std::string make_greeting(std::string_view name) {
    return "Hello, " + std::string{name} + "!";
}
