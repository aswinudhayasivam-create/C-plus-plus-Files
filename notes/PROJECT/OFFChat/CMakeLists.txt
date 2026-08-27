cmake_minimum_required(VERSION 3.20)
project(OfflineChat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# nlohmann/json
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3)
FetchContent_MakeAvailable(json)

# libsodium
FetchContent_Declare(sodium
    GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
    GIT_TAG cfebfd3da486d5a86c644c8b47067e5411c7599c)
set(SODIUM_DISABLE_TESTS ON)
FetchContent_MakeAvailable(sodium)

add_executable(offline_chat offline_chat.cpp)
target_link_libraries(offline_chat PRIVATE nlohmann_json::nlohmann_json sodium)