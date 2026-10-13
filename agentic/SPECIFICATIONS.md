# Agent Specifications

**Read this file before performing any work on this repository.**

---

## Role

Agents working on this project have three responsibilities:

1. **Build chain maintenance**
2. **Documentation**
3. **Bug fixes and best practices**

---

## 1. Build Chain Maintenance

### What this means

- Keep `CMakeLists.txt` up to date as source files are added or removed.
- When new `.cpp` files are added to `src/` or new headers to `include/`, verify they are picked up correctly. The current `file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)` handles this automatically — do not break that pattern.
- Ensure the compiled binary is always output to a `bin/` directory at the project root. If this is not yet enforced in `CMakeLists.txt`, add it.
- Match the C++ standard used to compile Geant4, queried at configure time via `geant4-config --cxxstd`. Do not hardcode the standard version.
- Do not hardcode any installation paths. Geant4 is located by the user sourcing `geant4.sh` before running cmake.

### Code style conventions

- Headers use `.hpp` extension, sources use `.cpp`.
- Headers live in `include/`, sources in `src/`.
- One class per file, filename matches the class name.
- Use `std::unique_ptr` for owned Geant4 objects where possible.
- Comments are in English, concise, and explain intent not mechanics.

### Binary output

The compiled binary `g4starter` must be placed in `bin/` at the project root. Enforce this in `CMakeLists.txt` with:

```cmake
set_target_properties(g4starter PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
```

If `bin/` is not already in `.gitignore`, add it.

---

## 2. Documentation

Agents are responsible for keeping the following documentation accurate and current:

### `README.md` (project root)

Must always contain:
- A brief description of what the project is.
- Build prerequisites (Geant4, CMake version).
- Step-by-step build instructions, including sourcing `geant4.sh`.
- Basic usage instructions for the compiled binary.

### Code-level documentation

- Every class must have a header comment describing its purpose.
- Non-obvious logic in `.cpp` files must have inline comments.
- `main.cpp` must describe the overall simulation flow.

### Keeping docs in sync

Whenever source files are added, modified, or removed, update `README.md` and any affected header comments in the same pass. Do not leave documentation out of date.

---

## 3. Bug Fixes and Best Practices

This project is a **learning sandbox**. The user writes the code and learns from it directly.

### What this means

- Agents may comb through the codebase and identify bugs, potential issues, and opportunities to apply C++ or Geant4 best practices.
- Findings must be presented as suggestions with clear explanations of what the issue is, why it matters, and what the recommended fix would look like.
- The agent must never apply corrections to user code on its own initiative.

### How to report findings

Present each finding with:
- **Location** — file and line/function
- **Issue** — what the problem or suboptimal pattern is
- **Why it matters** — the practical consequence (crash risk, undefined behavior, performance, maintainability, etc.)
- **Suggestion** — the recommended change, shown as a code snippet

Then wait for the user to decide whether and how to act on it.

### Scope

Agents may flag:
- Memory management issues (raw owning pointers, missing deletes, double-free risk)
- Undefined or implementation-defined behavior
- Violations of the code style conventions in section 1
- Geant4-specific antipatterns (e.g., incorrect use of the run manager lifecycle, thread-unsafe patterns in MT mode)
- Missing or misleading comments

---

## What agents must NOT do

- Hardcode paths to Geant4 or any library installation.
- Change the build system from CMake without explicit instruction.
- Introduce new external dependencies without flagging it to the user.
- Commit build artifacts (`build/`, `bin/`) to version control.
- Apply code corrections without explicit user approval.
