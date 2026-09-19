cmake_minimum_required(VERSION 3.16)

project(cpp_learning_examples VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(cpp_examples src/mylib.cpp)
target_include_directories(cpp_examples PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(hello_cpp src/main.cpp)
target_link_libraries(hello_cpp PRIVATE cpp_examples)

include(CTest)
if(BUILD_TESTING)
    add_executable(cpp_examples_tests tests/test_main.cpp)
    target_link_libraries(cpp_examples_tests PRIVATE cpp_examples)
    add_test(NAME cpp_examples_tests COMMAND cpp_examples_tests)
endif()
