# C++ Learning Files

This repository is a collection of C++ learning exercises, lab questions, and
small projects. Most files are intentionally standalone programs: they each
have their own `main()` function and should be compiled independently.

## Contents

- `src/` and `include/` contain a small, portable CMake example (`hello_cpp`).
- `tests/` contains assertions for the reusable root example library.
- `notes/INFO/` contains focused examples for fundamentals, arrays, strings,
  functions, pointers, classes, inheritance, polymorphism, templates,
  exceptions, and file handling.
- `notes/standrad questions/` contains number, function, and matrix practice.
- `notes/Lab Questions/` contains coursework-style exercises.
- `notes/PROJECT/` contains larger experiments, including games, chat tools,
  and bank-management iterations. Some projects require platform-specific or
  third-party dependencies.
- `Practice Questions/` contains additional problem-solving exercises.

The historical directory name `standrad questions` is retained to avoid moving
existing learning material. Depending on the platform, the final character in
that directory name may display differently.

## Requirements

- A compiler with C++17 support (for example GCC, Clang, or MSVC).
- CMake 3.16 or later for the root example and test target.

## Build and test the root example

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Run the example after building:

```sh
./build/hello_cpp
```

On Visual Studio or multi-configuration generators, the executable is usually
under `build/Debug` or `build/Release` instead.

## Compile an individual exercise

Because the exercises are independent, compile one file at a time. For example:

```sh
g++ -std=c++17 "Practice Questions/Addition game.cpp" -o addition_game
./addition_game
```

Some historical projects use macOS, Windows-console, Qt, libsodium, or
third-party JSON APIs. They are preserved as learning material and are not part
of the portable CMake build.

## Generated files

New compiler, CMake, IDE, and macOS debug-symbol outputs are ignored by
`.gitignore`. Existing historical output folders are retained because several
also contain project data and source snapshots.
