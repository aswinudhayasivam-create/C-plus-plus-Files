#include "mylib.hpp"

#include <cassert>

int main() {
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
}
