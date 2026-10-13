# Agent Handover Log

> **Before doing anything else, read `agentic/specifications.md`.** It defines the scope and rules for all agent work on this repository.

---

## Project Summary

`g4starter` is a minimal Geant4 simulation skeleton intended as boilerplate for new simulation projects. It compiles and runs a single geantino through a 1 m air cube using the FTFP_BERT physics list. The project is designed to be easy to extend and to support agentic maintenance of the build chain and documentation.

---

## Session History

### Session 1 — CMake setup and Geant4 discovery

**Problem:** Running `cmake ..` from the `build/` directory failed with:
> Could not find a package configuration file provided by "Geant4"

**Investigation:** `Geant4Config.cmake` was found at `/home/gvaldivi/Libraries/geant4-v11.4.3/install/lib/cmake/Geant4/`. The Geant4 installation was local, not system-wide, and not on CMake's search path.

**First attempt (rejected):** Passed `-DGeant4_DIR=...` pointing to the local install. This fixed the build but hardcoded a machine-specific path — not acceptable for a portable project.

**Correction:** Reverted to the general `find_package(Geant4 REQUIRED)` approach. The correct workflow is to source `geant4.sh` before running cmake:
```bash
source /path/to/geant4/install/bin/geant4.sh
cmake ..
```
This sets the necessary environment variables without touching the `CMakeLists.txt`. The `build/` directory is gitignored, so no machine-specific cache is ever committed.

**README updated** to document the `source geant4.sh` step as a prerequisite.

---

### Session 2 — C++ standard detection via geant4-config

**Problem:** The original `CMakeLists.txt` read the C++ standard from `Geant4_CXX_STANDARD`, a variable exported by `Geant4Config.cmake`. This variable is not guaranteed to be set by all Geant4 installs.

**Change:** Replaced the `Geant4_CXX_STANDARD` approach with a direct call to `geant4-config --cxxstd` at configure time using `execute_process`. The tool is located via `find_program` with a hint derived from `Geant4_DIR`, so it works even if `geant4-config` is not on `PATH`.

A sanity check validates the output is a plain integer before assigning it as `CMAKE_CXX_STANDARD`. CMake aborts with a clear error if `geant4-config` is missing or returns unexpected output.

**Result:** Configure output now reads:
```
-- C++ standard    : 20 (from geant4-config --cxxstd)
```

---

## Current State

| Item | Status |
|---|---|
| CMake configuration | Working — general, no hardcoded paths |
| C++ standard detection | Via `geant4-config --cxxstd` |
| Binary output directory | `bin/` — enforced via `set_target_properties` |
| `bin/` in `.gitignore` | Done |
| README | Up to date — includes build, usage, and agentic sections |
| Code documentation | Header comments added to all three classes |

---

## Known Gaps / Next Tasks

- `argc`/`argv` in `main()` are unused — no macro file handling yet (see Finding 3 in session 3).
- Geometry objects allocated with `new` lack ownership-transfer comments (cosmetic, see Finding 1 in session 3).

---

### Session 3 — First full agentic pass

**Triggered by:** New session, cold start from README.

**Actions taken (Role 1 — Build chain):**
- Added `set_target_properties` to `CMakeLists.txt` to route the binary to `bin/`.
- Added `bin` to `.gitignore`.
- Verified clean configure + full build; binary confirmed at `bin/g4starter`.

**Actions taken (Role 2 — Documentation):**
- Added class-level header comments to all three headers: `DefaultGeometry.hpp`, `ActionInitialization.hpp`, `PrimaryGeneratorAction.hpp`.
- Added a Usage section to `README.md` describing the binary location and what the simulation does.

**Findings reported (Role 3 — Bug fixes and best practices):**
Three suggestions presented to the user, no changes applied:
1. `DefaultGeometry.cpp` — ownership-transfer comment missing on geometry `new` allocations.
2. `main.cpp` — same issue for `SetUserInitialization` calls.
3. `main.cpp` — `argc`/`argv` are unused; no macro file handling present.
