# OpenCode Configuration for space_game

## Build Commands
- **Configure**: `cmake -S . -B build -D CMAKE_BUILD_TYPE=Release -D space_game_DEVELOPER_MODE=ON`
- **Build**: `cmake --build build`
- **Run**: `cmake --build build --target run-exe`
- **Test**: `cmake --build build && ctest --test-dir build`
- **Single test**: `cmake --build build && ./build/test/space_game_test`

## Lint/Format Commands
- **Format check**: `cmake --build build --target format-check`
- **Format fix**: `cmake --build build --target format-fix`

## Code Style Guidelines
- **Language**: C++20 standard
- **Namespace**: All code in `sms` namespace
- **Headers**: Use include guards (`#ifndef`/`#define`/`#endif`)
- **Includes**: raylib-cpp with `// IWYU pragma: export`, local headers with full paths from source/
- **Naming**: PascalCase for classes, camelCase for methods/variables, m_ prefix for members
- **Braces**: Opening brace on same line for functions/classes
- **Types**: Use `double` for floating point, `raylib::` prefix for raylib types
- **Error handling**: No exceptions visible in codebase, prefer return values
- **Comments**: Minimal, code should be self-documenting
- **Dependencies**: raylib/raylib-cpp for graphics, standard library otherwise