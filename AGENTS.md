**Agents Guide**

- Purpose: provide actionable build/test/lint commands and consistent coding rules for automated agents operating in this repository.
- Location: repository root — this file is `AGENTS.md`.

Build / Run / Test
- Build (out-of-source, CMake):

  ```bash
  mkdir -p build
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
  cmake --build build -- -j$(nproc)
  ```

- Debug build with compile commands (useful for clang-tidy/clangd):

  ```bash
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
  cmake --build build
  ```

- Run the program (built executable):

  ```bash
  ./build/rpgGame
  ```

- Run a single test (CTest):

  Notes: this repo currently has no CTest tests configured. If tests are added with `add_test()` in CMake, use:

  ```bash
  # run a single test whose name matches the regex 'MyTestName'
  cd build
  ctest -R 'MyTestName' --output-on-failure -V
  ```

  Or run a specific test executable directly (common for new test frameworks):

  ```bash
  ./build/tests/my_test_executable --gtest_filter=MyTestSuite.MyTest
  ```

- Run clang-tidy on a single file (requires `compile_commands.json` in `build`):

  ```bash
  run-clang-tidy-10 -clang-tidy-binary=$(which clang-tidy) -p build src/Character.cpp
  # or
  clang-tidy src/Character.cpp -p build --checks='*'
  ```

- Format a single file with clang-format:

  ```bash
  clang-format -i src/Character.cpp
  ```

- Quick static analysis / sanitizers (Debug build):

  ```bash
  cmake -S . -B build-sanit -DCMAKE_BUILD_TYPE=Debug -DSANITIZE=Address
  cmake --build build-sanit
  ./build-sanit/rpgGame
  ```

Repository / CI notes
- CMake target names: `Enemies`, `Weapons`, `GameCore`, and executable `rpgGame` (see `CMakeLists.txt`).
- `compile_commands.json` is produced when `CMAKE_EXPORT_COMPILE_COMMANDS` is ON — many tools depend on it.

Code Style Guidelines (for automated agents)
- Language: C++17. Default to the standards set in `CMakeLists.txt`.

- Formatting:
  - Use clang-format with a project style. If none exists, use LLVM style as baseline: `clang-format -style=llvm`.
  - Run `clang-format -i` on changed files before pushing.

- Includes ordering and style:
  - Use quoted includes for project headers: `#include "Character.h"`.
  - Use angle brackets for system headers: `#include <vector>`.
  - Order includes: 1) corresponding header (if in .cpp), 2) project headers (sorted), 3) third-party, 4) standard headers (sorted).
  - Avoid transitive includes in headers; prefer forward declarations when possible.

- Header files:
  - Use traditional include guards: `#ifndef FOO_H` / `#define FOO_H` / `#endif // FOO_H`.
  - Keep headers minimal: declare types and inline small functions only; implement in `.cpp` files.
  - Do not include heavy headers in other headers if forward declaration suffices.

- Naming conventions:
  - Types (classes/structs/enums): PascalCase (e.g., `Character`, `Enemy`, `Weapon`).
  - Member variables: `snake_case` or `camelCase` is acceptable; prefer `snake_case` or `m_` prefix if changing codebase-wide is feasible. Current code uses plain `name`, `health` — follow project pattern for edits.
  - Methods and functions: camelCase (e.g., `getName()`, `setHealth()`). Free functions: lowerCamelCase (e.g., `createEnemies`).
  - Constants and macros: ALL_CAPS (macros in repo: `CLEAR_COMMAND`, `COMBATANT_STATS_WIDTH`). Prefer `constexpr` or `const` variables in new code instead of macros.

- Types and integer widths:
  - Prefer fixed-width integer types for persistent or serialized data and tight bounds: `uint8_t`, `uint16_t`, `uint32_t`, etc. This repo already uses these — continue doing so.
  - For general counters or sizes use `size_t` when interacting with containers.

- Smart pointers / ownership:
  - Use `std::unique_ptr` for exclusive ownership and `std::shared_ptr` only when shared ownership is explicit. Use raw pointers only for non-owning observers.
  - Pass objects by const-reference (`const T&`) for read-only parameters; use value semantics when copying is cheap or intended.

- Error handling and logging:
  - For CLI utilities prefer explicit error returns and `std::cerr` for user-visible errors (matches existing code using `std::cerr` on file open failure).
  - Use exceptions for unrecoverable library errors only if the exception boundary is well-defined; otherwise, return error codes or `std::optional`/`Expected`-like types.
  - Always check I/O results (`ifstream.is_open()`, `std::getline()` return) and guard against malformed input. The repo follows this pattern in `loadWeaponFile()` — keep it.

- API / public surface guidance:
  - Keep interfaces small and explicit. Prefer non-throwing getters returning `const &` where appropriate.
  - Mark methods `noexcept` only when they are guaranteed not to throw.

- Concurrency / thread-safety:
  - This project is single-threaded; new multithreading must be documented and use standard concurrency primitives.

- Tests:
  - Add tests under `tests/` and register with CMake using `enable_testing()` and `add_test()` so `ctest` works.
  - Prefer linking test executables with `GameCore` and exercise pure logic without user input. Tests should be deterministic.

Repository hygiene for agents
- When editing files, preserve local style and existing naming unless performing a deliberate refactor across the codebase.
- Do not modify generated build artifacts under `build/` except for debugging. Prefer editing source under `src/` and `lib/`.
- Keep commits focused and small; when making multiple unrelated edits, split them into multiple commits/PRs.

Cursor / Copilot rules
- Cursor rules: none found in repository path `.cursor/` or `.cursorrules`.
- Copilot rules: no `.github/copilot-instructions.md` file found.

Guidance for automated agents (practical checklist)
1. Run `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON` and build.
2. Run `clang-tidy` (targeted files) using `-p build` to surface issues.
3. Apply `clang-format -i` to modified files before creating patches.
4. If adding tests, wire them into CMake (use `add_executable` + `add_test`) so `ctest` can run them and agents can target single tests with `ctest -R`.
5. Avoid committing binary/build artifacts; update only source, headers, and config.

If you are blocked
- If the build fails due to missing SDKs or tools, list the exact error and the command used.
- If a style decision is ambiguous (naming, header placement), follow the nearest existing file's pattern; if multiple styles exist, prefer the style used by the header you are editing.

Contact / Maintainer notes
- Maintainers: none listed in-repo. For PRs, add a short description: what changed, why, and how it was validated (build/tests).

End of file.
