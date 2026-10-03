#include "mylib.hpp"

#include <cctype>

namespace {
std::string_view trim_whitespace(std::string_view text) {
    while (!text.empty() && std::isspace(static_cast<unsigned char>(text.front()))) {
        text.remove_prefix(1);
    }
    while (!text.empty() && std::isspace(static_cast<unsigned char>(text.back()))) {
        text.remove_suffix(1);
    }
    return text;
}
}  // namespace

std::string make_greeting(std::string_view name) {
    const std::string_view trimmed = trim_whitespace(name);
    const std::string_view safe_name = trimmed.empty() ? std::string_view{"World"} : trimmed;
    return "Hello, " + std::string{safe_name} + "!";
}
