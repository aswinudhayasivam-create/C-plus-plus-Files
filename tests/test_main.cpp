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
}
