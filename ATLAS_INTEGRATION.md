# Atlas Engine Integration

This document explains the relationship between the **EVEOFFLINE** game project and the **Atlas Engine**, and how the two repositories work together.

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────┐
│                    EVEOFFLINE Repository                    │
│                  (This Repo — Game Project)                 │
│                                                             │
│  ┌───────────────────────────────────────────────────────┐  │
│  │              Atlas Engine (engine/)                    │  │
│  │  Generic, game-agnostic engine core                   │  │
│  │  • ECS Framework        • Graph VM + Compiler         │  │
│  │  • Asset System          • Networking (CS + P2P)       │  │
│  │  • Tick Scheduler        • World Layouts               │  │
│  │  • Hot Reload            • Lockstep + Rollback         │  │
│  └───────────────────────────────────────────────────────┘  │
│                          ▲                                  │
│                          │ links                            │
│              ┌───────────┼───────────┐                      │
│              │           │           │                      │
│  ┌───────────┴──┐  ┌─────┴────┐  ┌──┴──────────┐           │
│  │  cpp_client/  │  │ editor/  │  │ cpp_server/  │           │
│  │  Game Client  │  │  Editor  │  │ Game Server  │           │
│  │  (OpenGL)     │  │  (Dev)   │  │ (Dedicated)  │           │
│  └──────────────┘  └──────────┘  └─────────────┘           │
│                                                             │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐    │
│  │  data/   │  │  docs/   │  │  tools/  │  │ archive/ │    │
│  │  (JSON)  │  │          │  │          │  │ (Legacy) │    │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘    │
└─────────────────────────────────────────────────────────────┘
```

## Dual-Repository Strategy

### Current State (This Repository)

The Atlas Engine lives **inside** this repository under the `engine/` directory. This allows:

- Rapid iteration on both engine and game code
- Single build system for everything
- Easy debugging across engine/game boundaries

### Future State (Two Repositories)

The plan is to eventually split into two repositories:

| Repository | Purpose |
|------------|---------|
| **[Atlas](https://github.com/shifty81/Atlas)** | Standalone engine — generic, game-agnostic |
| **EVEOFFLINE** | Game project — uses Atlas as a dependency |

When the split happens:
1. The `engine/` and `editor/` directories move to the Atlas repo
2. This repo pulls Atlas as a submodule or external dependency
3. Game-specific code (`cpp_client/`, `cpp_server/`, `data/`) stays here

## Directory Structure

```
EVEOFFLINE/
├── engine/                 # ★ Atlas Engine (will move to Atlas repo)
│   ├── core/               #   Engine bootstrap, logging, config
│   ├── ecs/                #   Entity/Component/System framework
│   ├── graphvm/            #   Deterministic Graph VM + compiler
│   ├── assets/             #   Asset registry, binary format, hot reload
│   ├── net/                #   Networking (CS + P2P + lockstep/rollback)
│   ├── sim/                #   Tick scheduler, deterministic simulation
│   ├── world/              #   World layouts, WorldGraph, heightfield meshing
│   ├── project/            #   Project loading and validation
│   ├── command/            #   Undo/redo command system
│   ├── interaction/        #   Unified intent/utterance system
│   ├── voice/              #   Voice command registry
│   └── plugin/             #   Plugin validation and registry
│
├── editor/                 # ★ Atlas Editor (will move to Atlas repo)
│   ├── ui/                 #   Docking, layout, panel system
│   ├── panels/             #   ECS Inspector, Console, Project Picker,
│   │                       #   World Graph Editor, Voice Commands,
│   │                       #   Interaction Debugger, Net Inspector
│   ├── tools/              #   Game Packager, Asset Cooker
│   └── ai/                 #   AI Aggregator for asset generation
│
├── projects/               # ★ Atlas project files
│   ├── eveoffline/         #   EVEOFFLINE game as Atlas project
│   │   ├── eveoffline.atlas
│   │   ├── worlds/
│   │   └── strategy/
│   └── atlas-sample/       #   Minimal sample project
│
├── schemas/                # Versioned schemas
│   ├── atlas.project.v1.json
│   ├── atlas.worldgraph.v1.json
│   └── atlas.strategygraph.v1.json
│
├── atlas_tests/            # ★ Atlas Engine unit tests
│
├── cpp_client/             # EVEOFFLINE game client (stays here)
├── cpp_server/             # EVEOFFLINE game server (stays here)
├── data/                   # Game data — moddable JSON (stays here)
├── docs/                   # Documentation (stays here)
├── tools/                  # Modding tools (stays here)
└── archive/                # Legacy code (stays here)
```

## Building

### Build Everything

```bash
./scripts/build.sh
```

### Build Atlas Engine Only

```bash
make build-engine
```

### Run Atlas Engine Tests

```bash
make test-engine
```

### Build Game Client + Server (without Atlas Editor)

```bash
make build
```

### CMake Options

| Option | Default | Description |
|--------|---------|-------------|
| `BUILD_ATLAS_ENGINE` | `ON` | Build the Atlas Engine static library |
| `BUILD_ATLAS_EDITOR` | `OFF` | Build the Atlas Editor executable |
| `BUILD_ATLAS_TESTS` | `ON` | Build and register Atlas Engine tests |
| `BUILD_CLIENT` | `ON` | Build the EVEOFFLINE game client |
| `BUILD_SERVER` | `ON` | Build the EVEOFFLINE game server |

## Atlas Engine Design Principles

1. **Engine Is Not a Game** — The engine contains no gameplay logic; all game-specific code is in `cpp_client/` and `cpp_server/`
2. **Everything Is Data** — All behavior is authored as assets and executable graphs
3. **One Engine, Three Roles** — Editor, Client, and Server share the same engine core
4. **Determinism First** — All simulation is deterministic for networking and replay
5. **Hot-Reloadable Assets** — Zero-rebuild iteration during development

## Atlas Engine Components

### ECS Framework (`engine/ecs/`)
- Entity creation/destruction
- Type-safe component management (add, get, has, remove)
- Tick callbacks for system updates

### Graph VM (`engine/graphvm/`)
- Stack-based bytecode virtual machine
- Opcodes: arithmetic, comparison, branching, events
- Graph compiler: converts visual graph IR to bytecode
- Deterministic execution for networking

### Asset System (`engine/assets/`)
- Binary asset format (`.atlasb`) with magic number validation
- Asset registry with filesystem scanning
- Hot reload with file change detection
- Serialization utilities

### Networking (`engine/net/`)
- Client-Server and Peer-to-Peer modes
- Packet send/receive with type-tagged messages
- Peer management (add, remove, RTT tracking)
- Lockstep/rollback support with world snapshots
- Authority model (server/host authoritative)

### Simulation (`engine/sim/`)
- Fixed tick-rate scheduler
- Deterministic delta time
- Tick counting

### World Generation (`engine/world/`)
- Abstract WorldLayout interface
- Cube-sphere layout for planetary surfaces
- Voxel grid layout for block worlds
- LOD support, chunk neighbor queries, streaming hints
- Terrain mesh generation with height functions and normal computation
- Perlin noise and fractal Brownian motion (FBM) for procedural generation
- World streaming with load/unload radius and disk caching
- Galaxy generation with spiral arm structure and deterministic seeding
- **WorldGraph**: DAG-based world generation graph system
  - Typed ports and values (Float, HeightField, Seed, Mask, etc.)
  - Topological sort compilation with cycle and type-mismatch detection
  - Concrete nodes: Seed, Noise (FBM), Blend, Clamp, Constant
- **HeightfieldMesher**: Heightfield-to-mesh pipeline with LOD support

### Interaction System (`engine/interaction/`)
- Unified utterance/intent pipeline for voice, AI, console, and scripting
- Pattern-based intent resolver with case-insensitive matching
- Intent registry with named handlers for dispatching actions
- Supports: Command, Conversation, Debug, and Narrative interaction modes

### Voice Commands (`engine/voice/`)
- Voice command registry mapping phrases to intents
- Context-aware filtering (game, editor, both)
- Bridge between speech-to-text and the intent system

### Plugin System (`engine/plugin/`)
- Plugin descriptor with version compatibility and determinism flags
- Plugin validator enforcing engine compatibility
- Plugin registry for managing loaded extensions
- Plugin types: graph-extension, editor-panel, asset-importer

### Graph Commands (`engine/command/`)
- Undoable graph mutations via templated Command classes
- AddNodeCommand, RemoveNodeCommand, AddEdgeCommand, RemoveEdgeCommand
- Works with any graph type (SoundGraph, WorldGraph, RenderGraph, etc.)
- Integrates with CommandHistory for full undo/redo support

### RenderGraph (`engine/render/`)
- DAG-based GPU render pass scheduling
- Typed ports: Texture, Buffer, Float, PassConfig, DrawList
- Concrete nodes: ClearPass, GeometryPass, PostProcess, Present
- Deterministic pass ordering via topological sort
- Compile/Execute pipeline matching all other graph types

### ShaderGraph (`engine/shader/`)
- DAG-based shader/material composition
- Typed ports: Float, Vec2, Vec3, Vec4, Texture, Bool
- Concrete nodes: Multiply, Lerp, BaseColor, UVCoord
- Shaders as graphs — compile to data, not text
- Deterministic evaluation for caching and hot-reload

## Syncing with Atlas Repository

The `engine/` and `editor/` directories in this repo mirror the Atlas repo structure. To sync changes:

```bash
# From Atlas repo, copy engine changes
cp -r Atlas/engine/* EVEOFFLINE/engine/
cp -r Atlas/editor/* EVEOFFLINE/editor/

# Or from EVEOFFLINE to Atlas
cp -r EVEOFFLINE/engine/* Atlas/engine/
cp -r EVEOFFLINE/editor/* Atlas/editor/
```

Once the split is complete, this will be replaced with a git submodule or CMake `FetchContent`.

## Project Portability (Drag and Drop)

Atlas projects under `projects/` are designed to be **portable** between repos.
You can take the `eveoffline` folder from this repo and drop it into the Atlas
repo's `projects/` directory for testing.

### Requirements for Drag-and-Drop

1. The project must follow the structure defined in `docs/PROJECT_GUIDELINES.md`
2. It must have exactly one `.atlas` manifest file
3. All paths in the manifest must be relative (no absolute paths)
4. Required directories: `worlds/`, `assets/`, `data/`
5. No symlinks (cross-platform compatibility)

### Validating Portability

Before porting a project to another repo, run the validator:

```bash
./scripts/validate_project.sh projects/eveoffline
```

### Shared Data Handling

The `eveoffline` project references shared data at the repo root (`data/`)
through its `data/manifest.json`. When porting to the Atlas repo:

- Copy `data/` into the project folder, or
- Ensure the Atlas repo has a compatible `data/` directory at its root

### Building After Porting

The target repo must have:
- The Atlas Engine (`engine/` directory)
- A compatible CMake build system
- The project build script (`scripts/build_project.sh` or `scripts\build_project.bat`)

```bash
# In the target repo
./scripts/build_project.sh Release validate   # Check project structure
./scripts/build_project.sh Release all        # Build everything
```

## Related Documentation

- [Atlas Engine README](https://github.com/shifty81/Atlas/blob/main/README.md)
- [Atlas Development Roadmap](https://github.com/shifty81/Atlas/blob/main/docs/09_DEVELOPMENT_ROADMAP.md)
- [Atlas Future Plans](https://github.com/shifty81/EVEOFFLINE/commit/033f2f8e222e7bfa0f853123ed902c23d98c307a) — Detailed design discussion covering WorldGraph APIs, API cleanup, editor tools, and documentation tracks
- [Atlas Contributing Guide](https://github.com/shifty81/Atlas/blob/main/CONTRIBUTING.md)
- [EVEOFFLINE Roadmap](docs/ROADMAP.md)
- [EVEOFFLINE Modding Guide](docs/MODDING_GUIDE.md)
- [EVEOFFLINE Development Guidance](docs/DEVELOPMENT_GUIDANCE.md)
- [Project Context](PROJECT_CONTEXT.md) — Canonical project vision and design pillars
- [Atlas Naming Conventions](ATLAS_NAMING_CONVENTIONS.md) — Naming rules for components, systems, and files
- [Atlas Simulation Philosophy](ATLAS_SIMULATION_PHILOSOPHY.md) — Simulation design principles and layered architecture

## Phase 11: Background Simulation Layer

Phase 11 adds the background simulation systems that make the universe feel alive. These systems form the foundational layer for the dynamic economy, pirate threat escalation, and galactic response mechanics.

### New ECS Components (11 total)

| Component | Purpose |
|-----------|---------|
| `BackgroundSimState` | Galaxy-level simulation time and tick tracking |
| `SectorTension` | Per-system resource stress, pirate pressure, security |
| `NPCIntent` | AI intent selection (Mine, Haul, Trade, Patrol, Raid, etc.) |
| `TradeFlow` | Supply/demand flows with dynamic pricing |
| `PirateDoctrine` | Pirate coalition behavior state machine |
| `TitanAssemblyProgress` | Distributed titan construction with 6 assembly nodes |
| `GalacticResponse` | Faction response curves to perceived threats |
| `OperationalWear` | Ship deployment fatigue and logistics wear |
| `CaptainBackground` | Captain origin (Miner, Military, Corporate, etc.) |
| `FleetNorm` | Emergent fleet behavioral norms |

### New Systems (10 total)

| System | Layer | Purpose |
|--------|-------|---------|
| `BackgroundSimulationSystem` | 1 | Core galaxy simulation tick |
| `SectorTensionSystem` | 1 | Per-system resource/threat tracking |
| `TradeFlowSystem` | 1 | Economic supply/demand simulation |
| `NPCIntentSystem` | 1 | AI actor intent selection |
| `PirateDoctrineSystem` | 4 | Pirate coalition state machine |
| `TitanAssemblySystem` | 4 | Distributed titan construction pressure |
| `GalacticResponseSystem` | 4 | Faction escalation response curves |
| `OperationalWearSystem` | 1 | Ship logistics fatigue |
| `RumorPropagationSystem` | 3 | Rumor spreading between captains |
| `FleetNormSystem` | 3 | Fleet behavioral norm tracking |

### New Data Files

| File | Purpose |
|------|---------|
| `data/universe/titan_assembly.json` | Titan assembly node configuration |
| `data/universe/pirate_doctrine.json` | Pirate doctrine states and behavior rules |
| `data/universe/sector_defaults.json` | Default sector tension by security classification |
| `data/universe/galactic_response.json` | Faction response curves and thresholds |
| `data/fleet/captain_backgrounds.json` | Captain origin backgrounds and modifiers |
| `data/fleet/fleet_norms.json` | Fleet norm definitions and effects |

### System Update Order

The background simulation layer follows a strict update order (see [Atlas Simulation Philosophy](ATLAS_SIMULATION_PHILOSOPHY.md)):

1. BackgroundSimulationSystem → Galaxy time advances
2. SectorTensionSystem → Per-system tension updates
3. TradeFlowSystem → Economic flow calculations
4. PirateDoctrineSystem → Pirate behavior transitions
5. TitanAssemblySystem → Construction pressure (if enabled)
6. GalacticResponseSystem → Faction responses
7. NPCIntentSystem → Individual NPC decisions
8. OperationalWearSystem → Ship fatigue
9. RumorPropagationSystem → Information spreading
10. FleetNormSystem → Norm tracking
