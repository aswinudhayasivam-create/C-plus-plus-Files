#include "mylib.hpp"

#include <cstddef>

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
        case 0x180E:
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

unsigned int decode_utf8_codepoint(std::string_view text) {
    if (text.empty()) {
        return 0;
    }

    const unsigned char first = static_cast<unsigned char>(text.front());
    if ((first & 0x80u) == 0u) {
        return static_cast<unsigned int>(first);
    }
    if ((first & 0xE0u) == 0xC0u && text.size() >= 2) {
        const unsigned char second = static_cast<unsigned char>(text[1]);
        if ((second & 0xC0u) == 0x80u) {
            return ((static_cast<unsigned int>(first) & 0x1Fu) << 6) |
                   (static_cast<unsigned int>(second) & 0x3Fu);
        }
        return static_cast<unsigned int>(first);
    }
    if ((first & 0xF0u) == 0xE0u && text.size() >= 3) {
        const unsigned char second = static_cast<unsigned char>(text[1]);
        const unsigned char third = static_cast<unsigned char>(text[2]);
        if ((second & 0xC0u) == 0x80u && (third & 0xC0u) == 0x80u) {
            return ((static_cast<unsigned int>(first) & 0x0Fu) << 12) |
                   ((static_cast<unsigned int>(second) & 0x3Fu) << 6) |
                   (static_cast<unsigned int>(third) & 0x3Fu);
        }
        return static_cast<unsigned int>(first);
    }
    if ((first & 0xF8u) == 0xF0u && text.size() >= 4) {
        const unsigned char second = static_cast<unsigned char>(text[1]);
        const unsigned char third = static_cast<unsigned char>(text[2]);
        const unsigned char fourth = static_cast<unsigned char>(text[3]);
        if ((second & 0xC0u) == 0x80u && (third & 0xC0u) == 0x80u && (fourth & 0xC0u) == 0x80u) {
            return ((static_cast<unsigned int>(first) & 0x07u) << 18) |
                   ((static_cast<unsigned int>(second) & 0x3Fu) << 12) |
                   ((static_cast<unsigned int>(third) & 0x3Fu) << 6) |
                   (static_cast<unsigned int>(fourth) & 0x3Fu);
        }
        return static_cast<unsigned int>(first);
    }
    return static_cast<unsigned int>(first);
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
        const unsigned char second = static_cast<unsigned char>(text[1]);
        if ((second & 0xC0u) == 0x80u) {
            return 2;
        }
        return 1;
    }
    if ((first & 0xF0u) == 0xE0u && text.size() >= 3) {
        const unsigned char second = static_cast<unsigned char>(text[1]);
        const unsigned char third = static_cast<unsigned char>(text[2]);
        if ((second & 0xC0u) == 0x80u && (third & 0xC0u) == 0x80u) {
            return 3;
        }
        return 1;
    }
    if ((first & 0xF8u) == 0xF0u && text.size() >= 4) {
        const unsigned char second = static_cast<unsigned char>(text[1]);
        const unsigned char third = static_cast<unsigned char>(text[2]);
        const unsigned char fourth = static_cast<unsigned char>(text[3]);
        if ((second & 0xC0u) == 0x80u && (third & 0xC0u) == 0x80u && (fourth & 0xC0u) == 0x80u) {
            return 4;
        }
        return 1;
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
    if ((lead & 0xF8u) == 0xF0u) {
        const std::string_view candidate = text.substr(index, length);
        if (candidate.size() == 4 && (static_cast<unsigned char>(candidate[1]) & 0xC0u) == 0x80u &&
            (static_cast<unsigned char>(candidate[2]) & 0xC0u) == 0x80u &&
            (static_cast<unsigned char>(candidate[3]) & 0xC0u) == 0x80u) {
            return 4;
        }
    }
    if ((lead & 0xF0u) == 0xE0u) {
        const std::string_view candidate = text.substr(index, length);
        if (candidate.size() == 3 && (static_cast<unsigned char>(candidate[1]) & 0xC0u) == 0x80u &&
            (static_cast<unsigned char>(candidate[2]) & 0xC0u) == 0x80u) {
            return 3;
        }
    }
    if ((lead & 0xE0u) == 0xC0u) {
        const std::string_view candidate = text.substr(index, length);
        if (candidate.size() == 2 && (static_cast<unsigned char>(candidate[1]) & 0xC0u) == 0x80u) {
            return 2;
        }
    }
    return 1;
}

std::string_view trim_whitespace(std::string_view text) {
    while (!text.empty()) {
        const std::size_t length = utf8_codepoint_length(text);
        if (length == 0) {
            break;
        }

        std::string_view current = text.substr(0, length);
        const unsigned int codepoint = decode_utf8_codepoint(current);

        if (!is_whitespace_codepoint(codepoint)) {
            break;
        }
        text.remove_prefix(length);
    }

    while (!text.empty()) {
        const std::size_t length = utf8_codepoint_length_from_end(text);
        if (length == 0) {
            break;
        }

        std::string_view current = text.substr(text.size() - length, length);
        const unsigned int codepoint = decode_utf8_codepoint(current);

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
        if (codepoint_length == 0) {
            break;
        }

        std::string_view current = trimmed.substr(index, codepoint_length);
        const unsigned int codepoint = decode_utf8_codepoint(current);

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
