# Atlas Engine — Development Alignment Goals

This document maps the current project state to the target architecture defined
in the design specifications (1111.txt, 1112.md, 1114.txt, 2222) and establishes clear goals
for aligning the codebase with the new structure.

> **Note:** Design documents 1114.txt and 2222 introduced extensive new systems
> including graph modules, project restructuring, and platform-level features.

---

## Current State

The Atlas Engine is a C++20 modular game engine extracted from the EVEOFFLINE
project. It currently provides:

| Module | Status | Location |
|--------|--------|----------|
| Core (Engine, Logger) | ✅ Complete | `engine/core/` |
| ECS Framework | ✅ Complete | `engine/ecs/` |
| Graph VM + Compiler | ✅ Complete | `engine/graphvm/` |
| Graph Serialization | ✅ Complete | `engine/graphvm/` |
| Graph Cache | ✅ Complete | `engine/graphvm/` |
| Asset System | ✅ Complete | `engine/assets/` |
| Networking (CS + P2P) | ✅ Complete | `engine/net/` |
| Tick Scheduler | ✅ Complete | `engine/sim/` |
| World Generation | ✅ Complete | `engine/world/` |
| WorldGraph (DAG) | ✅ Complete | `engine/world/` |
| TileGraph (2D) | ✅ Complete | `engine/tile/` |
| Project System | ✅ Complete | `engine/project/` |
| Command System | ✅ Complete | `engine/command/` |
| Interaction System | ✅ Complete | `engine/interaction/` |
| Voice Commands | ✅ Complete | `engine/voice/` |
| Plugin System | ✅ Complete | `engine/plugin/` |
| StrategyGraph | ✅ Complete | `engine/strategygraph/` |
| Server Rules | ✅ Complete | `engine/rules/` |
| ConversationGraph | ✅ Complete | `engine/conversation/` |
| AI Signal Registry | ✅ Complete | `engine/ai/` |
| AI Memory | ✅ Complete | `engine/ai/` |
| Relationship Model | ✅ Complete | `engine/ai/` |
| BehaviorGraph | ✅ Complete | `engine/ai/` |
| SoundGraph | ✅ Complete | `engine/sound/` |
| CharacterGraph | ✅ Complete | `engine/character/` |
| AnimationGraph | ✅ Complete | `engine/animation/` |
| WeaponGraph | ✅ Complete | `engine/weapon/` |
| UIGraph | ✅ Complete | `engine/ui/` |
| GameFlowGraph | ✅ Complete | `engine/flow/` |
| Schema Validator | ✅ Complete | `engine/schema/` |
| Graph Commands | ✅ Complete | `engine/command/` |
| RenderGraph | ✅ Complete | `engine/render/` |
| ShaderGraph | ✅ Complete | `engine/shader/` |
| Node Editor Model | ✅ Complete | `engine/nodeeditor/` |
| Graph Diff | ✅ Complete | `engine/graphvm/` |
| Graph Timeline | ✅ Complete | `engine/graphvm/` |
| LLM Context Builder | ✅ Complete | `engine/ai/` |
| LLM Request Types | ✅ Complete | `engine/ai/` |
| LLM Response Validator | ✅ Complete | `engine/ai/` |
| LLM Cache | ✅ Complete | `engine/ai/` |
| Camera / World Modes | 🟡 Header-only | `engine/camera/` |
| Editor (panels, UI) | ✅ Complete | `editor/` |
| Node Graph Editor Panel | ✅ Complete | `editor/panels/` |
| AI Inspector Panel | ✅ Complete | `editor/panels/` |
| Runtime CLI | ✅ Complete | `runtime/` |

---

## Target Architecture (from 1112.md)

### Graph Types Required

| Graph | Purpose | Status |
|-------|---------|--------|
| WorldGraph | World generation | ✅ Implemented |
| StrategyGraph | AI decisions | ✅ Implemented |
| ConversationGraph | Dialogue + memory | ✅ Implemented |
| TileGraph | 2D world generation | ✅ Implemented |
| BehaviorGraph | AI behavior authoring | ✅ Implemented |
| SoundGraph | Procedural audio | ✅ Implemented |
| CharacterGraph | Modular character generation | ✅ Implemented |
| AnimationGraph | Animation + modifiers | ✅ Implemented |
| WeaponGraph | Weapon construction | ✅ Implemented |
| UIGraph | UI composition | ✅ Implemented |
| GameFlowGraph | Game flow state machine | ✅ Implemented |
| RenderGraph | GPU execution | ✅ Implemented |
| ShaderGraph | Materials | ✅ Implemented |

### AI Architecture Required

| Component | Purpose | Status |
|-----------|---------|--------|
| AISignalRegistry | Numeric inputs for AI | ✅ Implemented |
| ConversationGraph | Dialogue state | ✅ Implemented |
| StrategyGraph | Action decisions | ✅ Implemented |
| AI Memory + Decay | Persistent NPC memory | ✅ Implemented |
| Relationship Model | Entity relationships | ✅ Implemented |
| LLM Context Builder | LLM integration | ✅ Implemented |

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
| Node Graph Editor | ✅ Complete |
| AI Inspector | ✅ Complete |
| AI Prompt Debugger | ✅ Complete |
| AI Prompt Debugger | ✅ Complete |

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

- [x] Graph serialization format (JSON builder/reader)
- [x] Graph diff + undo support via Command system
- [x] ReadAISignal node for StrategyGraph
- [x] EmitAction node for StrategyGraph
- [x] AI Memory storage with tick-based decay
- [x] Relationship model (entity pairs → float)
- [x] ConversationGraph schema (atlas.conversation.v1.json)
- [x] TileGraph for 2D procedural generation
- [x] Graph execution caching + invalidation
- [x] SoundGraph for procedural audio
- [x] CharacterGraph for modular character generation
- [x] AnimationGraph for animation + modifiers
- [x] WeaponGraph for weapon construction
- [x] BehaviorGraph for AI behavior authoring
- [x] UIGraph for UI composition
- [x] GameFlowGraph for game flow state machine
- [x] Schema Validator for graph schema enforcement
- [x] EVE Offline project restructure (Plugin.toml, data manifest, AI config)
- [x] Arena2D reference project (multi-project scalability proof)
- [x] RenderGraph for GPU render pass scheduling
- [x] ShaderGraph for material/shader composition

### Phase C — Editor Tooling

Build the editor into a real authoring environment:

- [x] Visual node graph editor (canvas, pins, links)
- [x] AI Inspector panel (signals, memory, graphs)
- [x] AI Prompt Debugger panel (context + response)
- [x] Graph replay timeline scrubber
- [x] Graph diff preview (for AI-authored changes)
- [x] Undoable AI edits through Command system

### Phase D — LLM + AI Integration

Safe AI-assisted authoring:

- [x] AtlasLLMContextBuilder (context stack assembly)
- [x] LLM request type enforcement
- [x] Response schema validation
- [x] Deterministic cache storage (seeded, hashed, versioned)
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
