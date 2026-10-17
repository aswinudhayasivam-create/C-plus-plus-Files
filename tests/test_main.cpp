#include "mylib.hpp"

#include <cassert>

int main() {
    const std::string no_break_space("\xC2\xA0", 2);
    const std::string em_space("\xE2\x80\x83", 3);

    assert(make_greeting() == "Hello, World!");
    assert(make_greeting("C++") == "Hello, C++!");
    assert(make_greeting("learner") == "Hello, learner!");
    assert(make_greeting("") == "Hello, World!");
    assert(make_greeting("   ") == "Hello, World!");
    assert(make_greeting("\tC++\n") == "Hello, C++!");
    assert(make_greeting("  C++  ") == "Hello, C++!");
    assert(make_greeting("\n\t  \r") == "Hello, World!");
    assert(make_greeting(" \t \r\n \v\f ") == "Hello, World!");
    assert(make_greeting("  Alice Bob  ") == "Hello, Alice Bob!");
    assert(make_greeting("\tAlice\t") == "Hello, Alice!");
    assert(make_greeting("  Alice\t\nBob  ") == "Hello, Alice Bob!");
    assert(make_greeting(" Alice \t Bob ") == "Hello, Alice Bob!");
    assert(make_greeting("Alice" + no_break_space + "Bob") == "Hello, Alice Bob!");
    assert(make_greeting(em_space + "Alice" + em_space + "Bob" + em_space) == "Hello, Alice Bob!");
    const std::string figure_space("\xE2\x80\x87", 3);
    const std::string narrow_no_break_space("\xE2\x80\xAF", 3);
    assert(make_greeting(figure_space + "Alice" + figure_space + "Bob" + figure_space) == "Hello, Alice Bob!");
    assert(make_greeting(narrow_no_break_space + "Alice" + narrow_no_break_space + "Bob" + narrow_no_break_space) == "Hello, Alice Bob!");

    const std::string bom_prefix("\xEF\xBB\xBF", 3);
    const std::string zero_width_space("\xE2\x80\x8B", 3);
    const std::string zero_width_non_joiner("\xE2\x80\x8C", 3);
    const std::string zero_width_joiner("\xE2\x80\x8D", 3);
    const std::string word_joiner("\xE2\x81\xA0", 3);
    const std::string invisible_times("\xE2\x81\xA2", 3);
    const std::string invisible_plus("\xE2\x81\xA5", 3);
    const std::string left_to_right_mark("\xE2\x80\x8E", 3);
    const std::string right_to_left_mark("\xE2\x80\x8F", 3);
    const std::string text_isolate("\xE2\x81\xA6", 3);
    const std::string mongolian_vowel_separator("\xE1\xA0\x8E", 3);
    assert(make_greeting(bom_prefix + "Alice" + bom_prefix) == "Hello, Alice!");
    assert(make_greeting(zero_width_space + "Alice" + zero_width_space + "Bob" + zero_width_space) == "Hello, Alice Bob!");
    assert(make_greeting(zero_width_non_joiner + "Alice" + zero_width_non_joiner + "Bob" + zero_width_non_joiner) == "Hello, Alice Bob!");
    assert(make_greeting(zero_width_joiner + "Alice" + zero_width_joiner + "Bob" + zero_width_joiner) == "Hello, Alice Bob!");
    assert(make_greeting(word_joiner + "Alice" + word_joiner + "Bob" + word_joiner) == "Hello, Alice Bob!");
    assert(make_greeting(invisible_times + "Alice" + invisible_times + "Bob" + invisible_times) == "Hello, Alice Bob!");
    assert(make_greeting(invisible_plus + "Alice" + invisible_plus + "Bob" + invisible_plus) == "Hello, Alice Bob!");
    assert(make_greeting(left_to_right_mark + "Alice" + left_to_right_mark + "Bob" + left_to_right_mark) == "Hello, Alice Bob!");
    assert(make_greeting(right_to_left_mark + "Alice" + right_to_left_mark + "Bob" + right_to_left_mark) == "Hello, Alice Bob!");
    assert(make_greeting(text_isolate + "Alice" + text_isolate + "Bob" + text_isolate) == "Hello, Alice Bob!");
    assert(make_greeting(mongolian_vowel_separator + "Alice" + mongolian_vowel_separator + "Bob" + mongolian_vowel_separator) == "Hello, Alice Bob!");

    const std::string control_whitespace = std::string() + char(0x1C) + char(0x1D) + char(0x1E) + char(0x1F) +
        'A' + 'l' + 'i' + 'c' + 'e' + char(0x1C) + char(0x1D) + char(0x1E) + char(0x1F);
    assert(make_greeting(control_whitespace) == "Hello, Alice!");
}
