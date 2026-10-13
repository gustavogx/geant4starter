# g4starter

Boilerplate code for a functioning Geant4 simulation. See different branches and tags for versions and options.

## Agentic Support

This project includes guidance for AI agents. If you are a model assisting with this repository, read the following files before doing any work:

- `agentic/SPECIFICATIONS.md` — defines the three agent roles: build chain maintenance, documentation, and bug fixes/best practices. Also contains code style conventions and hard constraints.
- `agentic/HANDOVER.md` — session history, past decisions, known gaps, and current project state.

## Building

Requires a Geant4 installation. Before configuring, source the Geant4 environment script so CMake can find it:

```bash
source /path/to/geant4/install/bin/geant4.sh
```

Then build as usual:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Add the `source` line to your `~/.bashrc` (or `~/.profile`) to avoid running it every session. The C++ standard is detected automatically from the Geant4 install.

## Usage

After a successful build the binary is at `bin/g4starter` (relative to the project root). Run it directly:

```bash
./bin/g4starter
```

The simulation fires one geantino from the center of a 1 m air cube along the +Z axis using the FTFP_BERT physics list. A geantino is a non-interacting tracking particle — it traverses the geometry without depositing energy, making it useful for verifying geometry definitions before adding real physics.
