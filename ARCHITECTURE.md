# Atlas Engine — Architecture

This document defines the **baseline architecture** for the Atlas Engine, establishing the
structural contracts and module boundaries that all development must follow.

## Overview

Atlas is a **deterministic, tool-first game engine** extracted from the EVEOFFLINE game project.
It separates reusable engine systems from game-specific content, enabling multiple projects to
share the same core technology.

```
Atlas/
├── engine/           # Atlas Engine (game-agnostic static library)
│   ├── core/         # Engine lifecycle, logging, capabilities
│   ├── ecs/          # Entity-Component-System framework
│   ├── graphvm/      # Deterministic bytecode graph VM
│   ├── assets/       # Asset registry, binary format, hot reload
│   ├── net/          # Networking (client-server, P2P, lockstep/rollback)
│   ├── sim/          # Tick scheduler, deterministic simulation
│   ├── world/        # Procedural world generation (terrain, galaxy, noise)
│   ├── project/      # Project loading and validation (.atlas files)
│   └── command/      # Undo/redo command system
│
├── editor/           # Atlas Editor (authoring tool)
│   ├── panels/       # Inspector panels (ECS, console, network)
│   ├── ui/           # Dock layout, panel framework
│   ├── tools/        # Game packager, asset tools
│   └── ai/           # AI assistant aggregator
│
├── runtime/          # Atlas Runtime (standalone executable)
│
├── atlas_tests/      # Engine unit tests
│
├── schemas/          # Versioned project schemas
│   └── atlas.project.v1.json
│
├── cpp_client/       # EVEOFFLINE game client (links AtlasEngine)
├── cpp_server/       # EVEOFFLINE game server (links AtlasEngine)
├── data/             # Moddable game content (JSON)
├── tools/            # Modding utilities (Blender addon, validators)
└── docs/             # Design documents, guides, session logs
```

## Engine Modules

### Core (`engine/core/`)
- **Engine**: Lifecycle management, mode selection (Editor/Client/Server)
- **Logger**: Structured logging
- **Capabilities**: Role-based feature gating (AssetWrite, Rendering, NetAuthority, etc.)

### ECS (`engine/ecs/`)
- Type-safe entity creation and destruction
- Component storage via `std::any` (type-indexed)
- Per-tick update callbacks

### Graph VM (`engine/graphvm/`)
- Deterministic bytecode virtual machine
- Graph IR (nodes + edges) compiled to linear opcodes
- Arithmetic, comparison, branching, variables, events

### Assets (`engine/assets/`)
- Binary asset format (`.atlasb`) with header, type, version
- Registry with filesystem scanning
- Hot-reload via file timestamp polling

### Networking (`engine/net/`)
- Modes: Standalone, Client, Server, P2P_Host, P2P_Peer
- Packet-based send/receive with tick stamping
- Peer management (add, remove, RTT tracking)
- Snapshot save/rollback/replay for lockstep networking

### Simulation (`engine/sim/`)
- Fixed-rate tick scheduler
- Deterministic time stepping

### World Generation (`engine/world/`)
- Cube-sphere planetary projection with LOD
- Voxel grid chunked layout
- Perlin/FBM noise generation (seeded, deterministic)
- Terrain mesh generation with normals
- World streaming with disk cache
- Galaxy generation (star systems, regions, star classes)

### Project System (`engine/project/`)
- Load and validate `.atlas` project files
- Schema-versioned project format (`atlas.project.v1`)
- Module references (world graphs, strategy graphs, AI)
- Runtime configuration (entry world, tick rate)

### Command System (`engine/command/`)
- Abstract `Command` base with Execute/Undo
- `CommandHistory` for undo/redo stacks
- Foundation for editor mutations and multiplayer sync

## Runtime Modes

| Mode   | Rendering | Networking | Asset Write | Graph Edit |
|--------|-----------|------------|-------------|------------|
| Editor | ✅         | Optional   | ✅           | ✅          |
| Client | ✅         | ✅          | ❌           | ❌          |
| Server | ❌         | ✅          | ❌           | ❌          |

## Determinism Contract

All simulation systems must satisfy:

> **Same project + same seed + same inputs = same outputs (always)**

Rules:
- No system clock access in simulation
- No global RNG — use injected `DeterministicRNG` only
- No threading outside the tick scheduler
- Fixed-point or deterministic floating-point only

## Project Schema

Projects are defined by a single `project.atlas` JSON file conforming to
`schemas/atlas.project.v1.json`. See the schema file for the full specification.

## Build System

The root `CMakeLists.txt` controls all build targets. **All targets are ON by default**
so a single build produces every executable, making everything debuggable at the same time.

| Option              | Default | Description                     |
|---------------------|---------|---------------------------------|
| BUILD_ATLAS_ENGINE  | ON      | Atlas Engine static library     |
| BUILD_ATLAS_TESTS   | ON      | Engine unit tests               |
| BUILD_ATLAS_EDITOR  | ON      | Atlas Editor application        |
| BUILD_ATLAS_RUNTIME | ON      | Atlas Runtime application       |
| BUILD_CLIENT        | ON      | EVEOFFLINE game client          |
| BUILD_SERVER        | ON      | EVEOFFLINE game server          |

Individual targets can be disabled when only a subset is needed (e.g. CI engine-only builds).

## Testing

All engine modules have corresponding test files in `atlas_tests/`.
Tests use `assert()` with `[PASS]` output and are registered in `main.cpp`.
Run with: `make test-engine`
