#pragma once

#include <string>
#include <string_view>

// Returns the greeting used by the small, buildable root example.
// If name is empty, the function falls back to "World".
std::string make_greeting(std::string_view name = "World");
