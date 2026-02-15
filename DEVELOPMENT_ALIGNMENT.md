# Atlas Engine — Development Alignment Goals

This document maps the current project state to the target architecture defined
in the design specifications (1111.txt, 1112.md) and establishes clear goals
for aligning the codebase with the new structure.

> **Note:** A future design document (1112 series) may introduce additional
> changes. Review incoming spec files before starting new feature work.

---

## Current State

The Atlas Engine is a C++20 modular game engine extracted from the EVEOFFLINE
project. It currently provides:

| Module | Status | Location |
|--------|--------|----------|
| Core (Engine, Logger) | ✅ Complete | `engine/core/` |
| ECS Framework | ✅ Complete | `engine/ecs/` |
| Graph VM + Compiler | ✅ Complete | `engine/graphvm/` |
| Asset System | ✅ Complete | `engine/assets/` |
| Networking (CS + P2P) | ✅ Complete | `engine/net/` |
| Tick Scheduler | ✅ Complete | `engine/sim/` |
| World Generation | ✅ Complete | `engine/world/` |
| WorldGraph (DAG) | ✅ Complete | `engine/world/` |
| Project System | ✅ Complete | `engine/project/` |
| Command System | ✅ Complete | `engine/command/` |
| Interaction System | ✅ Complete | `engine/interaction/` |
| Voice Commands | ✅ Complete | `engine/voice/` |
| Plugin System | ✅ Complete | `engine/plugin/` |
| StrategyGraph | ✅ Complete | `engine/strategygraph/` |
| Server Rules | ✅ Complete | `engine/rules/` |
| ConversationGraph | ✅ Complete | `engine/conversation/` |
| AI Signal Registry | ✅ Complete | `engine/ai/` |
| Camera / World Modes | 🟡 Header-only | `engine/camera/` |
| Editor (panels, UI) | ✅ Complete | `editor/` |
| Runtime CLI | ✅ Complete | `runtime/` |

---

## Target Architecture (from 1112.md)

### Graph Types Required

| Graph | Purpose | Status |
|-------|---------|--------|
| WorldGraph | World generation | ✅ Implemented |
| StrategyGraph | AI decisions | ✅ Implemented |
| ConversationGraph | Dialogue + memory | ✅ Implemented |
| RenderGraph | GPU execution | 📋 Planned |
| ShaderGraph | Materials | 📋 Planned |
| TileGraph | 2D world generation | 📋 Planned |

### AI Architecture Required

| Component | Purpose | Status |
|-----------|---------|--------|
| AISignalRegistry | Numeric inputs for AI | ✅ Implemented |
| ConversationGraph | Dialogue state | ✅ Implemented |
| StrategyGraph | Action decisions | ✅ Implemented |
| AI Memory + Decay | Persistent NPC memory | 📋 Planned |
| Relationship Model | Entity relationships | 📋 Planned |
| LLM Context Builder | LLM integration | 📋 Planned |

### Editor Panels Required

| Panel | Status |
|-------|--------|
| ECS Inspector | ✅ Exists (stub) |
| Console | ✅ Complete |
| Network Inspector | ✅ Exists (stub) |
| Project Picker | ✅ Complete |
| World Graph Editor | ✅ Complete |
| Voice Commands | ✅ Complete |
| Interaction Debugger | ✅ Complete |
| Game Packager | ✅ Complete |
| AI Inspector | 📋 Planned (1112.md) |
| AI Prompt Debugger | 📋 Planned (1112.md) |

---

## Development Goals

### Phase A — Foundation (Current Sprint)

These items align the project with the core architecture:

- [x] ProjectManager singleton (`Get()`, `Unload()`, `ProjectRoot()`)
- [x] Editor `--project` CLI support
- [x] StrategyGraph engine module with compile/execute
- [x] Server Rules system for live parameter tuning
- [x] ConversationGraph engine module (Dialogue, PlayerChoice, MemoryWrite, RelationshipDelta)
- [x] AI Signal Registry (namespaced read/write)
- [x] CameraProjectionPolicy / WorldMode enum
- [x] SANDBOXING.md documentation
- [x] ARCHITECTURE.md updated with new modules
- [x] Unit tests for all new modules

### Phase B — Graph Ecosystem

Extend the graph system to cover all required types:

- [ ] Graph serialization format (JSON `.worldgraph` / `.strategygraph` / `.conversation`)
- [ ] Graph diff + undo support via Command system
- [ ] ReadAISignal node for StrategyGraph
- [ ] EmitAction node for StrategyGraph
- [ ] AI Memory storage with tick-based decay
- [ ] Relationship model (entity pairs → float)
- [ ] TileGraph for 2D procedural generation
- [ ] Graph execution caching + invalidation

### Phase C — Editor Tooling

Build the editor into a real authoring environment:

- [ ] Visual node graph editor (canvas, pins, links)
- [ ] AI Inspector panel (signals, memory, graphs)
- [ ] AI Prompt Debugger panel (context + response)
- [ ] Graph replay timeline scrubber
- [ ] Graph diff preview (for AI-authored changes)
- [ ] Undoable AI edits through Command system

### Phase D — LLM + AI Integration

Safe AI-assisted authoring:

- [ ] AtlasLLMContextBuilder (context stack assembly)
- [ ] LLM request type enforcement
- [ ] Response schema validation
- [ ] Deterministic cache storage (seeded, hashed, versioned)
- [ ] AI graph authoring sandbox (diff-only, human-approved)

### Phase E — Multiplayer & Replay

Determinism enforcement at scale:

- [ ] AI replay capture format
- [ ] Replay diff tool
- [ ] CI determinism tests (graph hash stability)
- [ ] Server-side AI execution model
- [ ] AI replication packets
- [ ] Client-side visualization-only AI

### Phase F — Plugin & Mod Ecosystem

Safe extensibility:

- [ ] Plugin binary symbol scanner
- [ ] Plugin permission manifests
- [ ] Mod manifest parsing
- [ ] Mod overlay resolver (load-order based)
- [ ] AI signal namespace enforcement for mods
- [ ] WASM plugin support (future)

---

## Rules for New Development

1. **Every new module must have tests** — registered in `atlas_tests/main.cpp`
2. **Every graph type follows the same pattern** — DAG, Compile, Execute, typed ports
3. **No module may break determinism** — same inputs = same outputs, always
4. **Editor and runtime are separate** — editor authors data, runtime executes data
5. **AI is never an authority** — AI proposes, humans approve, commands execute
6. **Check incoming spec files** — 1112 series and beyond may alter priorities

---

## Related Documents

- [Architecture](ARCHITECTURE.md) — Module structure and contracts
- [Project Guidelines](docs/PROJECT_GUIDELINES.md) — Rules for Atlas projects
- [Sandboxing Policy](SANDBOXING.md) — Plugin and AI safety rules
- [Simulation Philosophy](ATLAS_SIMULATION_PHILOSOPHY.md) — Determinism and layering
- [Naming Conventions](ATLAS_NAMING_CONVENTIONS.md) — Code style rules
