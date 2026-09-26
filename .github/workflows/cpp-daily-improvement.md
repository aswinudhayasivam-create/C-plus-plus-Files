---
name: Daily C++ Improvement

on:
  schedule:
    - cron: "30 3 * * *"
  workflow_dispatch:

permissions:
  contents: read

engine:
  id: copilot
  model: copilot/auto
tools:
  bash:
    - "g++ --version"
    - "g++ -std=c++17"
    - "git diff"
    - "git status"
  edit:
  github:
    toolsets:
      - repos

safe-outputs:
  create-pull-request:
    max: 1
    title-prefix: "[Daily C++] "
    labels:
      - automated
      - cpp-maintenance
---
# Daily C++ Repository Maintenance

Inspect the repository and perform genuine maintenance on the C++ learning code.

## Objective

Each scheduled run may improve **up to 2 C++ source files**.

Prioritize files under:

- `Practice Questions/`
- `src/`
- other directories containing `.cpp`, `.cc`, `.cxx`, or `.hpp` files

Do not make cosmetic changes.

## What counts as a meaningful improvement

Look for real issues such as:

- incorrect program logic
- incorrect calculations
- invalid input handling
- boundary-condition bugs
- incorrect array or matrix handling
- unsafe memory usage
- missing error handling
- incorrect output
- obvious portability problems
- simple code-structure improvements that preserve the educational purpose

Preserve the original learning style of the program.

Do not unnecessarily rewrite complete programs.

## Repository learning constraints

Avoid introducing concepts that are inconsistent with the existing beginner/intermediate C++ exercises.

Do not introduce:

- `vector`
- unnecessary STL containers
- `fstream`
- `cstring`

unless the specific existing program already depends on them.

Prefer simple:

- arrays
- loops
- functions
- classes
- pointers
- basic standard C++ features

## File selection

Select at most 2 files.

Before changing a file:

1. Read the complete source.
2. Understand what the program is intended to do.
3. Identify a genuine issue.
4. Make the smallest reasonable correction.
5. Preserve the original program's purpose.

If no meaningful improvement is available, do not invent one.

## Validation

After modifying each file:

1. Compile it when possible.
2. Check for compiler errors.
3. Test the changed behavior when practical.
4. Inspect the final diff.
5. Make sure unrelated files were not modified.

Use a simple C++ compiler command such as:

```bash
g++ -std=c++17 <source-file> -o /tmp/gh-aw/agent/test_program
