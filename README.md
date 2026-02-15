<p align="center">
  <img src="docs/images/banner.svg" alt="Atlas — PVE Space Simulator" width="900"/>
</p>

<h3 align="center">A PVE-focused space simulator for solo play and small groups (2–20 players)</h3>
<p align="center">
  Built with <b>C++20 / OpenGL</b> and the custom <b>Atlas Engine</b> — a modular, deterministic game engine
</p>

<p align="center">
  <code>Status: Active R&D</code> · <code>Platforms: Linux · macOS · Windows</code> · <code>License: TBD</code>
</p>

---

## What Is This?

**Atlas-EveOffline** is a PVE space simulation inspired by EVE Online — rebuilt from scratch
with a custom engine. AI drives the universe: economy, pirates, factions, and fleet behavior
all run whether or not the player is watching.

The **Atlas Engine** underneath is game-agnostic and designed for extraction into a
[standalone engine](https://github.com/shifty81/Atlas).

---

## 🗺️ Roadmap

```
  COMPLETED                          IN PROGRESS                       PLANNED
  ─────────                          ───────────                       ───────
  ✅ Phase 1  Core Engine            🔧 Engine Migration               📋 Phase 8   Cinematic Warp
     ECS, networking, tick sim          StrategyGraph module            📋 Phase 9   Fleet AI
  ✅ Phase 2  Content                   ConversationGraph module        📋 Phase 10  Tactical Overlay
     102 ships, 159 modules             AI Signal Registry              📋 Phase 11  Fleet Civilization
  ✅ Phase 3  Economy                   Server Rules system             📋 Phase 12  Ship Gen v2
     Manufacturing, market              World Modes / Camera
  ✅ Phase 4  Social                    Editor project loading       ┌──────────────────────┐
     Corps, contracts, chat             Sandboxing policy            │  🎯 NEXT MILESTONE   │
  ✅ Phase 5  3D Graphics                                            │                      │
     OpenGL, PBR, particles          🔧 Documentation                │  Vertical Slice      │
  ✅ Phase 6  Tech II                   README overhaul               │  One full star       │
     HAC, Recon, Logistics              Development alignment         │  system, playable    │
  ✅ Phase 7  Industry                  Architecture updates          │  loop, AI-driven     │
     Mining, PI, wormholes                                            └──────────────────────┘
```

> **[Full Roadmap →](docs/ROADMAP.md)** · **[Development Alignment →](DEVELOPMENT_ALIGNMENT.md)**

---

## 🏗️ Architecture

```
Atlas/
├── engine/                 ← Atlas Engine (game-agnostic, 17 modules)
│   ├── core/                  Engine lifecycle, logging
│   ├── ecs/                   Entity-Component-System
│   ├── graphvm/               Deterministic bytecode VM
│   ├── assets/                Binary assets, hot reload
│   ├── net/                   Client-Server + P2P networking
│   ├── sim/                   Fixed-rate tick scheduler
│   ├── world/                 WorldGraph, terrain, galaxy gen
│   ├── strategygraph/         Strategy decision graphs (AI)
│   ├── conversation/          Dialogue + memory graphs
│   ├── ai/                    AI signal registry
│   ├── rules/                 Server rules (live tuning)
│   ├── camera/                World modes + projection
│   ├── project/               .atlas project loading
│   ├── command/               Undo/redo system
│   ├── interaction/           Unified intent system
│   ├── voice/                 Voice command registry
│   └── plugin/                Plugin validation + sandbox
│
├── editor/                 ← Atlas Editor (authoring tool)
├── runtime/                ← Atlas Runtime (standalone exe)
├── atlas_tests/            ← Engine unit tests (97 tests)
├── schemas/                ← Versioned project schemas
├── projects/               ← Game projects (.atlas files)
│   ├── eveoffline/            EVEOFFLINE reference project
│   └── atlas-sample/          Minimal sample project
│
├── cpp_client/             ← EVEOFFLINE game client (OpenGL)
├── cpp_server/             ← EVEOFFLINE dedicated server
├── data/                   ← Moddable game content (JSON)
├── tools/                  ← Modding utilities
└── docs/                   ← Documentation (40+ files)
```

> **[Architecture →](ARCHITECTURE.md)** · **[Integration Guide →](ATLAS_INTEGRATION.md)** · **[Project Guidelines →](docs/PROJECT_GUIDELINES.md)**

---

## 🚀 Quick Start

```bash
# Linux/macOS — install deps and build everything
sudo apt-get install build-essential cmake libgl1-mesa-dev libglew-dev \
  libglfw3-dev libglm-dev nlohmann-json3-dev libopenal-dev libfreetype-dev
./build.sh

# Windows — use vcpkg + Visual Studio
generate_solution.bat --open

# CMake (any platform) — single build produces all executables
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

# Run engine tests
make test-engine

# Load a project
./build/runtime/AtlasRuntime --project projects/eveoffline/eveoffline.atlas --validate-only
```

---

## 🔩 Engine Modules

| Module | What It Does |
|--------|-------------|
| **ECS** | Entity/Component/System with type-safe components |
| **Graph VM** | Deterministic bytecode VM for visual scripting |
| **WorldGraph** | DAG-based procedural world generation |
| **StrategyGraph** | AI decision graphs (influence, threat, scoring) |
| **ConversationGraph** | Dialogue, player choices, memory, relationships |
| **AI Signals** | Namespaced numeric inputs for AI systems |
| **Server Rules** | Live parameter tuning with replay awareness |
| **Networking** | Client-Server + P2P with lockstep/rollback |
| **Asset System** | Binary format, registry, hot reload |
| **Project System** | `.atlas` manifest loading and validation |
| **Command System** | Undo/redo for editor and multiplayer sync |
| **Plugin System** | Validated, sandboxed extensions |

---

## 🎮 Game Features

<table>
<tr><td width="50%" valign="top">

**Combat & Movement**
- Module activation, target locking, damage types, EW
- Approach, orbit, keep-at-range, warp, align
- Fleet system with AI or human wingmates

**Ships & Factions**
- 102 ships across frigates → titans
- Tech I + Tech II specializations
- 4 factions: Solari · Veyren · Aurelian · Keldari

</td><td width="50%" valign="top">

**Economy & Industry**
- Mining, manufacturing, market, contracts
- AI miners, haulers, pirates drive the economy
- Resources extracted → moved → produced → destroyed

**Exploration & Missions**
- Probe scanning, deadspace, wormholes
- 5 levels × 7 mission types
- 137 skills across 20 categories

</td></tr>
</table>

---

## 🔧 Modding

All game content is JSON in `data/` — fully moddable:

```
data/ships/     102+ ship definitions       data/universe/   Solar systems, stargates
data/modules/   159+ module definitions      data/missions/   Mission templates
data/skills/    137 skill definitions        data/market/     Economy and pricing
```

**Tools:** `validate_json.py` · `create_ship.py` · `BlenderSpaceshipGenerator/`
→ **[Modding Guide](docs/MODDING_GUIDE.md)**

---

## 📚 Documentation

| Topic | Links |
|-------|-------|
| **Getting Started** | [Tutorial](docs/TUTORIAL.md) · [Build Guides](docs/guides/) |
| **Engine** | [Architecture](ARCHITECTURE.md) · [Integration](ATLAS_INTEGRATION.md) · [Sandboxing](SANDBOXING.md) |
| **Development** | [Alignment Goals](DEVELOPMENT_ALIGNMENT.md) · [Roadmap](docs/ROADMAP.md) · [Contributing](docs/CONTRIBUTING.md) |
| **Design** | [Project Context](PROJECT_CONTEXT.md) · [Simulation Philosophy](ATLAS_SIMULATION_PHILOSOPHY.md) · [Naming](ATLAS_NAMING_CONVENTIONS.md) |
| **Schemas** | [Project Schema](schemas/atlas.project.v1.json) · [WorldGraph](schemas/atlas.worldgraph.v1.json) · [StrategyGraph](schemas/atlas.strategygraph.v1.json) |

---

## 🤝 Contributing

Contributions are welcome! See [CONTRIBUTING.md](docs/CONTRIBUTING.md).

**Rules:** Every new module needs tests · No breaking determinism · Editor authors data, runtime executes data

## 📝 License

[To be determined]

---

<sub>Atlas is an indie PVE space simulator. All in-game content uses original naming conventions. Not affiliated with CCP Games.</sub>
