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

std::string normalize_name(std::string_view name) {
    const std::string_view trimmed = trim_whitespace(name);
    if (trimmed.empty()) {
        return "World";
    }

    std::string normalized;
    normalized.reserve(trimmed.size());
    bool last_was_space = false;

    for (const unsigned char ch : trimmed) {
        if (std::isspace(ch)) {
            if (!normalized.empty() && !last_was_space) {
                normalized.push_back(' ');
                last_was_space = true;
            }
        } else {
            normalized.push_back(static_cast<char>(ch));
            last_was_space = false;
        }
    }

    return normalized;
}
}  // namespace

std::string make_greeting(std::string_view name) {
    return "Hello, " + normalize_name(name) + "!";
}
