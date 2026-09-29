#include "mylib.hpp"

#include <cassert>

int main() {
    assert(make_greeting() == "Hello, World!");
    assert(make_greeting("C++") == "Hello, C++!");
    assert(make_greeting("learner") == "Hello, learner!");
    assert(make_greeting("") == "Hello, World!");
}
