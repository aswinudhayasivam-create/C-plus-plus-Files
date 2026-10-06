#include "mylib.hpp"

#include <cctype>

namespace {
bool is_whitespace_codepoint(unsigned int codepoint) {
    switch (codepoint) {
        case 0x09:
        case 0x0A:
        case 0x0B:
        case 0x0C:
        case 0x0D:
        case 0x20:
        case 0x85:
        case 0xA0:
        case 0x1680:
        case 0x2000:
        case 0x2001:
        case 0x2002:
        case 0x2003:
        case 0x2004:
        case 0x2005:
        case 0x2006:
        case 0x2007:
        case 0x2008:
        case 0x2009:
        case 0x200A:
        case 0x200B:
        case 0x2028:
        case 0x2029:
        case 0x202F:
        case 0x205F:
        case 0x3000:
        case 0xFEFF:
            return true;
        default:
            return false;
    }
}

std::size_t utf8_codepoint_length(std::string_view text) {
    if (text.empty()) {
        return 0;
    }

    const unsigned char first = static_cast<unsigned char>(text.front());
    if ((first & 0x80u) == 0u) {
        return 1;
    }
    if ((first & 0xE0u) == 0xC0u && text.size() >= 2) {
        return 2;
    }
    if ((first & 0xF0u) == 0xE0u && text.size() >= 3) {
        return 3;
    }
    if ((first & 0xF8u) == 0xF0u && text.size() >= 4) {
        return 4;
    }
    return 1;
}

std::size_t utf8_codepoint_length_from_end(std::string_view text) {
    if (text.empty()) {
        return 0;
    }

    std::size_t index = text.size() - 1;
    std::size_t length = 1;
    while (index > 0 && (static_cast<unsigned char>(text[index]) & 0xC0u) == 0x80u) {
        --index;
        ++length;
    }

    const unsigned char lead = static_cast<unsigned char>(text[index]);
    if ((lead & 0xF0u) == 0xF0u) {
        return 4;
    }
    if ((lead & 0xE0u) == 0xE0u) {
        return 3;
    }
    if ((lead & 0xC0u) == 0xC0u) {
        return 2;
    }
    return 1;
}

std::string_view trim_whitespace(std::string_view text) {
    while (!text.empty()) {
        const std::size_t length = utf8_codepoint_length(text);
        const std::string_view current = text.substr(0, length);
        unsigned int codepoint = static_cast<unsigned int>(static_cast<unsigned char>(current.front()));

        if (current.size() == 2) {
            codepoint = ((codepoint & 0x1Fu) << 6) | (static_cast<unsigned int>(static_cast<unsigned char>(current.back())) & 0x3Fu);
        } else if (current.size() == 3) {
            codepoint = ((codepoint & 0x0Fu) << 12) |
                        ((static_cast<unsigned int>(static_cast<unsigned char>(current[1])) & 0x3Fu) << 6) |
                        (static_cast<unsigned int>(static_cast<unsigned char>(current[2])) & 0x3Fu);
        } else if (current.size() == 4) {
            codepoint = ((codepoint & 0x07u) << 18) |
                        ((static_cast<unsigned int>(static_cast<unsigned char>(current[1])) & 0x3Fu) << 12) |
                        ((static_cast<unsigned int>(static_cast<unsigned char>(current[2])) & 0x3Fu) << 6) |
                        (static_cast<unsigned int>(static_cast<unsigned char>(current[3])) & 0x3Fu);
        }

        if (!is_whitespace_codepoint(codepoint)) {
            break;
        }
        text.remove_prefix(length);
    }

    while (!text.empty()) {
        const std::size_t length = utf8_codepoint_length_from_end(text);
        const std::string_view current = text.substr(text.size() - length, length);
        unsigned int codepoint = static_cast<unsigned int>(static_cast<unsigned char>(current.front()));

        if (current.size() == 2) {
            codepoint = ((codepoint & 0x1Fu) << 6) | (static_cast<unsigned int>(static_cast<unsigned char>(current.back())) & 0x3Fu);
        } else if (current.size() == 3) {
            codepoint = ((codepoint & 0x0Fu) << 12) |
                        ((static_cast<unsigned int>(static_cast<unsigned char>(current[1])) & 0x3Fu) << 6) |
                        (static_cast<unsigned int>(static_cast<unsigned char>(current[2])) & 0x3Fu);
        } else if (current.size() == 4) {
            codepoint = ((codepoint & 0x07u) << 18) |
                        ((static_cast<unsigned int>(static_cast<unsigned char>(current[1])) & 0x3Fu) << 12) |
                        ((static_cast<unsigned int>(static_cast<unsigned char>(current[2])) & 0x3Fu) << 6) |
                        (static_cast<unsigned int>(static_cast<unsigned char>(current[3])) & 0x3Fu);
        }

        if (!is_whitespace_codepoint(codepoint)) {
            break;
        }
        text.remove_suffix(length);
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
    std::size_t index = 0;

    while (index < trimmed.size()) {
        const std::size_t codepoint_length = utf8_codepoint_length(trimmed.substr(index));
        std::string_view current = trimmed.substr(index, codepoint_length);
        unsigned int codepoint = static_cast<unsigned int>(static_cast<unsigned char>(current.front()));

        if (current.size() == 2) {
            codepoint = ((codepoint & 0x1Fu) << 6) | (static_cast<unsigned int>(static_cast<unsigned char>(current.back())) & 0x3Fu);
        } else if (current.size() == 3) {
            codepoint = ((codepoint & 0x0Fu) << 12) |
                        ((static_cast<unsigned int>(static_cast<unsigned char>(current[1])) & 0x3Fu) << 6) |
                        (static_cast<unsigned int>(static_cast<unsigned char>(current[2])) & 0x3Fu);
        } else if (current.size() == 4) {
            codepoint = ((codepoint & 0x07u) << 18) |
                        ((static_cast<unsigned int>(static_cast<unsigned char>(current[1])) & 0x3Fu) << 12) |
                        ((static_cast<unsigned int>(static_cast<unsigned char>(current[2])) & 0x3Fu) << 6) |
                        (static_cast<unsigned int>(static_cast<unsigned char>(current[3])) & 0x3Fu);
        }

        if (is_whitespace_codepoint(codepoint)) {
            if (!normalized.empty() && !last_was_space) {
                normalized.push_back(' ');
                last_was_space = true;
            }
        } else {
            normalized.append(current.begin(), current.end());
            last_was_space = false;
        }

        index += codepoint_length;
    }

    return normalized;
}
}  // namespace

std::string make_greeting(std::string_view name) {
    return "Hello, " + normalize_name(name) + "!";
}
