AGENTS.md
=========

Purpose
- Short, actionable instructions for agentic editors working on this C++ project.
- Covers build, run, lint, test commands and a code-style checklist agents must follow.

Quick repository layout
- Root-level CMakeLists.txt builds libs from `src/` and headers are in `lib/`.
- Build output and `compile_commands.json` live in `build/` after running CMake.
- Executable produced: `build/rpgGame`.

Important operational note for agents
- I (the automated assistant) can create or edit files in this workspace, but I cannot commit changes to git or push to remote. A human must run `git add`/`git commit`/`git push` when they want changes recorded in version control.

Build / run commands
- Configure (recommended):
  - `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release`
- Build:
  - `cmake --build build -- -j$(nproc)`
- One-liner quick build:
  - `cmake -S . -B build && cmake --build build`
- Clean rebuild:
  - `rm -rf build && cmake -S . -B build && cmake --build build`
- Run the executable:
  - `./build/rpgGame`
- Alternative using Makefile in build (if present):
  - `make -C build`

Testing
- This repository currently has no test targets. Recommended approach: add GoogleTest via CMake and register tests with CTest.
- Run tests (once configured):
  - `cd build && ctest --output-on-failure`
- Run a single test:
  1. Using ctest by test name or regex:
     - `cd build && ctest -R TestName -V`
  2. Using the gtest binary directly:
     - `./build/tests/my_tests --gtest_filter=MySuite.MyTest`
- TIP: use `ctest -j<N>` to parallelize test execution.

Linting & static analysis
- Ensure `compile_commands.json` exists (CMake: CMAKE_EXPORT_COMPILE_COMMANDS ON).
- Formatting (clang-format):
  - Install clang-format (v10+ recommended).
  - Add a repo `.clang-format` (preferred). If missing, agents should default to LLVM style.
  - Format changed files before committing: `clang-format -i <files>` or use `git ls-files` pattern: `clang-format -i $(git ls-files '*.h' '*.hpp' '*.cpp')`.
- Static analysis (clang-tidy):
  - `run-clang-tidy -p build` or run `clang-tidy file.cpp -- -Ilib -std=c++17` using flags from compile_commands.json.
- Optional: add cpplint or other linters for additional style checks.

Single-file quick compile
- To compile and run one file quickly, extract flags from `compile_commands.json` or use:
  - `clang++ -std=c++17 -Ilib -I. src/foo.cpp -o /tmp/foo && /tmp/foo`

Code style and conventions (required)
- Language & standard:
  - C++17 (CMAKE_CXX_STANDARD = 17). Follow portable, idiomatic C++17.
- Formatting:
  - Use the repository `.clang-format`. If none exists, use LLVM style.
  - Always run clang-format on files you change.
- Indentation:
  - Honor `.clang-format`. In absence of that, prefer 4 spaces.
- Includes:
  - Include only what you use. Prefer forward declarations in headers where possible to reduce compile-time dependencies.
  - Never put `using namespace std;` in headers. Avoid `using` directives in headers entirely.
  - In headers prefer explicit `std::` qualifiers (e.g., `std::string`). Small, local `using` in .cpp files is acceptable.
- Header guards & header style:
  - For new headers prefer `#pragma once`.
  - When editing existing files, follow the file's current guard style to avoid churn.
  - Keep declarations in headers and definitions in .cpp files unless templates or true inline functions.
  - Header files should contain only declarations/prototypes; put the actual implementations in `.cpp` files (except for templates or intentionally inline functions).
- Naming conventions:
  - Types (classes, structs, enums): PascalCase (e.g., `Character`, `SuperMutant`).
  - Functions and variables: camelCase (e.g., `getHealth`, `setBottlecaps`).
  - Private members in new code: prefer trailing underscore (e.g., `health_`). When editing existing code, prefer minimal disruption; follow local style.
  - File names: match type names where possible (`Weapon.h`, `Weapon.cpp`).
  - Constants: SCREAMING_SNAKE_CASE or prefer `enum class` with PascalCase enumerators.
- Getter / Setter specifics (project preference):
  - Use full, descriptive variable names in getters/setters (avoid cryptic abbreviations).
  - Header declarations must use the full parameter name: e.g., `void setBottlecaps(int bottlecaps);`.
  - In implementations assign with explicit `this->` to disambiguate member from parameter:
    - `void Character::setBottlecaps(int bottlecaps) { this->bottlecaps = bottlecaps; }`
  - Return getters as `const T&` where the lifetime guarantees safety; otherwise return by value. Mark getters `const` when appropriate.
- Types & ownership:
  - Use value semantics for small POD-like types.
  - For polymorphic hierarchies avoid storing by value (prevents slicing). Prefer `std::unique_ptr<Base>` or `std::shared_ptr<Base>` for owning containers.
  - Use smart pointers for ownership; raw pointers are non-owning observers only.
  - Pass large objects as `const T&` and use `T&&`/std::move for transfers.
- Const-correctness:
  - Mark member functions `const` when they do not modify state.
  - Use `const` parameters when data is not changed.
- Error handling:
  - Prefer explicit error signaling: return `bool`, `std::optional<T>`, or error codes for recoverable errors.
  - Reserve exceptions for truly exceptional conditions and document exception-safety if used.
  - Document error conditions in public APIs.
- Logging & IO:
  - Avoid printing from library code; let `main` or a designated CLI layer handle user-facing output.
  - Use `std::cerr` for diagnostics in CLI code or a small logging helper.
- Threading:
  - Codebase is single-threaded. If adding concurrency, document thread-safety and prefer safe primitives.
- Tests & assertions:
  - Use `assert()` for internal invariants during development.
  - Add unit tests for new features and for any bugfixes.
- Documentation & comments:
  - Document class invariants, ownership, and any non-obvious behavior in headers.
  - Prefer clear naming over excessive comments.

Practical checks & common pitfalls
- Object slicing: some classes currently store `Weapon` by value. If `Weapon` becomes polymorphic, convert storage to smart pointers.
- Header/implementation mismatches: double-check const qualifiers and signatures between .h and .cpp.
- Missing return/typo errors: run a build and clang-tidy after edits — these catches are common.

Local verification steps before opening a PR
1. Build: `cmake -S . -B build && cmake --build build`
2. Format: run `clang-format -i` on changed files.
3. Static analysis: run `run-clang-tidy -p build` and triage findings.
4. Tests: add and run unit tests for new behavior where applicable.

Git & commit guidance for agents
- I can modify files but I cannot create commits or push branches. A human must run:
  - `git add <files>`
  - `git commit -m "<short message>"` (title ≤ 72 chars; optional body explaining why)
  - `git push` (if desired)
- Commit message format: short title, blank line, 1–3 lines explaining why the change was made.

Cursor / Copilot rules
- No `.cursor` or `.cursorrules` files were found in the repo root or subfolders at the time of this scan.
- No `.github/copilot-instructions.md` file was present.
- If such files are added later they must be read and followed — they override general guidance in this AGENTS.md when applicable.

What to do on first edit / PR
- Make a minimal, focused change per PR.
- Run build, format and static checks locally.
- Add unit tests for behavioral changes.
- Explain the rationale and list verification steps in the PR description.

Suggested follow-ups (helpful to the project)
1. Add a `.clang-format` file and enforce formatting in CI.
2. Add a clang-tidy configuration and a CI run for static analysis.
3. Add a basic GoogleTest harness and one or two unit tests for core interactions (Character vs Enemy).

Contact & escalation
- If design intent is unclear (ownership model, lifetime expectations, polymorphic design), open an issue and ask the repository owner before making large refactors.

End of file.
