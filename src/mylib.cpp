#include "mylib.hpp"

#include <cstddef>

namespace {
constexpr unsigned int kUnicodeReplacementCharacter = 0xFFFDu;
constexpr std::string_view kUnicodeReplacementUtf8 = "\xEF\xBF\xBD";

bool is_utf8_continuation(unsigned char byte) {
    return (byte & 0xC0u) == 0x80u;
}

bool is_whitespace_codepoint(unsigned int codepoint) {
    if (codepoint <= 0x20u) {
        return true;
    }

    switch (codepoint) {
        case 0x7Fu:
        case 0x85u:
        case 0xA0u:
        case 0x00ADu:
        case 0x061Cu:
        case 0x115Fu:
        case 0x1160u:
        case 0x17B4u:
        case 0x17B5u:
        case 0x180Eu:
        case 0x1680u:
        case 0x2028u:
        case 0x2029u:
        case 0x202Fu:
        case 0x205Fu:
        case 0x3000u:
        case 0xFEFFu:
            return true;
        default:
            break;
    }

    if (codepoint >= 0x2000u && codepoint <= 0x200Au) {
        return true;
    }
    if (codepoint >= 0x200Bu && codepoint <= 0x200Fu) {
        return true;
    }
    if (codepoint >= 0x202Au && codepoint <= 0x202Eu) {
        return true;
    }
    if (codepoint >= 0x2060u && codepoint <= 0x206Fu) {
        return true;
    }

    return false;
}

bool decode_utf8_codepoint(std::string_view text, std::size_t offset, unsigned int& codepoint, std::size_t& length) {
    if (offset >= text.size()) {
        return false;
    }

    const unsigned char first = static_cast<unsigned char>(text[offset]);
    if ((first & 0x80u) == 0u) {
        codepoint = first;
        length = 1;
        return true;
    }

    if ((first & 0xE0u) == 0xC0u) {
        if (offset + 2 > text.size()) {
            return false;
        }
        const unsigned char second = static_cast<unsigned char>(text[offset + 1]);
        if (!is_utf8_continuation(second)) {
            return false;
        }
        const unsigned int candidate = ((static_cast<unsigned int>(first) & 0x1Fu) << 6) |
                                       (static_cast<unsigned int>(second) & 0x3Fu);
        if (candidate >= 0x80u && candidate <= 0x7FFu && !(candidate >= 0xD800u && candidate <= 0xDFFFu)) {
            codepoint = candidate;
            length = 2;
            return true;
        }
        return false;
    }

    if ((first & 0xF0u) == 0xE0u) {
        if (offset + 3 > text.size()) {
            return false;
        }
        const unsigned char second = static_cast<unsigned char>(text[offset + 1]);
        const unsigned char third = static_cast<unsigned char>(text[offset + 2]);
        if (!is_utf8_continuation(second) || !is_utf8_continuation(third)) {
            return false;
        }
        const unsigned int candidate = ((static_cast<unsigned int>(first) & 0x0Fu) << 12) |
                                       ((static_cast<unsigned int>(second) & 0x3Fu) << 6) |
                                       (static_cast<unsigned int>(third) & 0x3Fu);
        if (candidate >= 0x800u && candidate <= 0xFFFFu && !(candidate >= 0xD800u && candidate <= 0xDFFFu)) {
            codepoint = candidate;
            length = 3;
            return true;
        }
        return false;
    }

    if ((first & 0xF8u) == 0xF0u) {
        if (offset + 4 > text.size()) {
            return false;
        }
        const unsigned char second = static_cast<unsigned char>(text[offset + 1]);
        const unsigned char third = static_cast<unsigned char>(text[offset + 2]);
        const unsigned char fourth = static_cast<unsigned char>(text[offset + 3]);
        if (!is_utf8_continuation(second) || !is_utf8_continuation(third) || !is_utf8_continuation(fourth)) {
            return false;
        }
        const unsigned int candidate = ((static_cast<unsigned int>(first) & 0x07u) << 18) |
                                       ((static_cast<unsigned int>(second) & 0x3Fu) << 12) |
                                       ((static_cast<unsigned int>(third) & 0x3Fu) << 6) |
                                       (static_cast<unsigned int>(fourth) & 0x3Fu);
        if (candidate >= 0x10000u && candidate <= 0x10FFFFu) {
            codepoint = candidate;
            length = 4;
            return true;
        }
        return false;
    }

    return false;
}

void append_utf8(std::string& text, unsigned int codepoint) {
    if (codepoint <= 0x7Fu) {
        text.push_back(static_cast<char>(codepoint));
        return;
    }
    if (codepoint <= 0x7FFu) {
        text.push_back(static_cast<char>(0xC0u | (codepoint >> 6)));
        text.push_back(static_cast<char>(0x80u | (codepoint & 0x3Fu)));
        return;
    }
    if (codepoint <= 0xFFFFu) {
        text.push_back(static_cast<char>(0xE0u | (codepoint >> 12)));
        text.push_back(static_cast<char>(0x80u | ((codepoint >> 6) & 0x3Fu)));
        text.push_back(static_cast<char>(0x80u | (codepoint & 0x3Fu)));
        return;
    }
    text.push_back(static_cast<char>(0xF0u | (codepoint >> 18)));
    text.push_back(static_cast<char>(0x80u | ((codepoint >> 12) & 0x3Fu)));
    text.push_back(static_cast<char>(0x80u | ((codepoint >> 6) & 0x3Fu)));
    text.push_back(static_cast<char>(0x80u | (codepoint & 0x3Fu)));
}

std::string_view trim_whitespace(std::string_view text) {
    std::size_t start = 0;
    while (start < text.size()) {
        unsigned int codepoint = 0;
        std::size_t length = 0;
        if (!decode_utf8_codepoint(text, start, codepoint, length)) {
            break;
        }
        if (!is_whitespace_codepoint(codepoint)) {
            break;
        }
        start += length;
    }

    std::size_t end = text.size();
    while (end > start) {
        std::size_t codepoint_start = end;
        if (codepoint_start > start) {
            --codepoint_start;
            while (codepoint_start > start && (static_cast<unsigned char>(text[codepoint_start]) & 0xC0u) == 0x80u) {
                --codepoint_start;
            }
        }

        unsigned int codepoint = 0;
        std::size_t length = 0;
        if (!decode_utf8_codepoint(text, codepoint_start, codepoint, length)) {
            break;
        }
        if (codepoint_start + length > end) {
            break;
        }
        if (!is_whitespace_codepoint(codepoint)) {
            break;
        }
        end = codepoint_start;
    }

    return text.substr(start, end - start);
}

std::string normalize_name(std::string_view name) {
    const std::string_view trimmed = trim_whitespace(name);
    if (trimmed.empty()) {
        return "World";
    }

    std::string normalized;
    bool last_was_space = false;
    std::size_t index = 0;
    while (index < trimmed.size()) {
        unsigned int codepoint = 0;
        std::size_t length = 0;
        if (!decode_utf8_codepoint(trimmed, index, codepoint, length)) {
            append_utf8(normalized, kUnicodeReplacementCharacter);
            ++index;
            last_was_space = false;
            continue;
        }

        if (is_whitespace_codepoint(codepoint)) {
            if (!normalized.empty() && !last_was_space) {
                normalized.push_back(' ');
                last_was_space = true;
            }
            index += length;
            continue;
        }

        append_utf8(normalized, codepoint);
        last_was_space = false;
        index += length;
    }

    return normalized.empty() ? "World" : normalized;
}
}  // namespace

std::string make_greeting(std::string_view name) {
    return "Hello, " + normalize_name(name) + "!";
}
