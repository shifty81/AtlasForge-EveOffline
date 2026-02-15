# Archive

This directory contains legacy, deprecated, and completed files from the Atlas project's
development history. Everything here is kept for historical reference only — the active
codebase and current documentation live in the repository root and `docs/`.

---

## Contents

### `status_reports/` — Completed Status Reports & Merged Content
Documents that recorded project milestones, implementation completions, bug fixes,
and action plans that have since been fulfilled. Archived because their content has
been incorporated into the active codebase and current documentation.

- `FINAL_SUMMARY.md` — C++ OpenGL feature integration completion summary
- `FIX_SUMMARY.md` — CMake external dependencies fix documentation
- `GUI_INTEGRATION_SUMMARY.md` — GUI integration completion (Context Menu & Radial Menu)
- `IMPLEMENTATION_COMPLETE.md` — EVE gameplay loops and 3D support completion
- `IMPLEMENTATION_SUMMARY.md` — Full EVE Online experience implementation summary
- `IMMEDIATE_ACTION_PLAN.md` — Post-baseline action plan (superseded by DEVELOPMENT_GUIDANCE)
- `NAMING_CONVENTION.md` — UI rename mapping (applied; see ATLAS_NAMING_CONVENTIONS.md)
- `NEXT_TASKS.md` — Historical task tracking (superseded by ROADMAP.md)
- `PHASE6_COMPLETE.md` — Phase 6 completion summary (C++ server & client)
- `PR_DESCRIPTION.md` — CMake build error fix PR description
- `PROJECT_STATUS_FEB2026.md` — Baseline systems completion snapshot (27/27 systems)
- `PROJECT_SUMMARY.md` — Full EVE OFFLINE engine implementation summary
- `QUICK_REFERENCE.md` — Legacy Python-based quick reference (superseded by main README)
- `SHIP_GENERATION_NEXT_STEPS.md` — Ship generation integration steps (completed)
- `SHIP_MODELING_SUMMARY.md` — Ship modeling enhancements and capital ships summary
- `SOLUTION.md` — CMake/ImGui build error solution
- `SOLUTION_GLEW_DEPENDENCY.md` — GLEW dependency error resolution
- `VS2022_IMPLEMENTATION_SUMMARY.md` — VS2022 build support implementation
- `WORK_COMPLETED.md` — Phase 3 systems completion summary

### `sessions/` — Development Session Summaries
Historical session notes from development work. Not authoritative references.

**Original session summaries:**
- `SESSION_SUMMARY.md` — Phase 5 development session (Feb 2, 2026)
- `SESSION_SUMMARY_CONTINUE_NEXT_STEPS_FEB2026.md` — Repository analysis session (Feb 11, 2026)
- `SESSION_SUMMARY_GUI_PHASE7.md` — GUI Phase 7 rendering session (Feb 11, 2026)
- `SESSION_SUMMARY_NEXT_TASKS.md` — Phase review session (Feb 7, 2026)

**`docs_sessions/` — Completed phase session logs (moved from `docs/sessions/`):**

All 37 session files covering Phases 2–7 have been archived here. These document
completed development sessions including:

- C++ client, ECS, OpenGL, and network implementation sessions
- Phase 2–7 completion records (rendering, UI, audio, mining, Tech II, etc.)
- Build automation, deferred rendering, shadow mapping, post-processing sessions
- Procedural generation, model loading, and integrated hosting sessions
- Planning and review sessions (Feb 2026)

### `development/` — Completed Phase Development Docs
Phase-specific implementation documentation for work that has been completed and
merged into the codebase. Moved from `docs/development/`.

- `PHASE5_*.md` (6 files) — Phase 5 enhancements, polish, UI/UX, visual features
- `PHASE6_*.md` (2 files) — Phase 6 content expansion and ship models
- `PHASE7_*.md` (4 files) — Phase 7 mining, ice, planetary interaction, research
- `CLIENT_INTEGRATION_SUMMARY.md` — Client integration completion
- `CLIENT_UPDATES.md` — Python client updates (superseded by C++ client)
- `CHAT_LOG.md` — Development chat log
- `INTEGRATED_MULTIPLAYER_HOSTING.md` — Embedded server hosting
- `IMPLEMENTATION_DETAILS.md` — GUI implementation guide
- `NAME_GENERATOR.md` — Random name generation
- `PLAYER_STRUCTURES.md` — Player-owned structures
- `VISUAL_FEATURES_GUIDE.md` — Visual features reference
- `VISUAL_GAMEPLAY_ENHANCEMENTS.md` — Visual enhancements

### `features/` — Completed Feature Summaries
Feature documentation for systems that are fully implemented. Moved from `docs/features/`.

- `FEATURE_IMPLEMENTATION_SUMMARY.md` — Feature implementation guide
- `PHASE3_SYSTEMS.md` — Manufacturing, market, exploration
- `PHASE4_FEATURES.md` — Corporation and social systems
- `UI_IMPLEMENTATION_SUMMARY.md` — EVE Online UI implementation
- `NEW_FEATURES.md` — Module fitting and game systems
- `EXTENDED_CONTENT_SUMMARY.md` — Content pack summary
- `EVE_UI_ENHANCEMENTS.md` — EVE Photon UI documentation
- `VISUAL_CAPABILITIES.md` — Visual and GUI capabilities
- `LANGUAGE_AND_3D_OPTIONS.md` — Python vs C++ discussion (decided: C++)

### `design/` — Completed Design Documents
Design specifications for decisions that have been made and implemented.
Moved from `docs/design/`.

- `CPP_CLIENT_ARCHITECTURE.md` — C++ client architecture (implemented)
- `CPP_MIGRATION_ROADMAP.md` — C++ migration plan (completed)
- `EVE_MECHANICS.md` — EVE Online mechanics reference
- `EVE_UI_STYLE_REFERENCE.md` — Photon UI design reference
- `EVE_UNIVERSE_LAYOUT.md` — Universe layout and travel mechanics
- `PHASE5_3D_SPECIFICATION.md` — Phase 5 3D specification
- `PHASE5_SUMMARY.md` — Phase 5 summary
- `UI_FRAMEWORK_EVALUATION.md` — UI framework analysis (decided: custom Atlas UI)

### `research/` — Completed Research
Research and analysis documents. Moved from `docs/research/`.

- `ASTROX_RESEARCH.md` — Astrox Imperium technical research
- `OBJ_MODEL_ANALYSIS.md` — Analysis of 311 OBJ ship models

### `getting-started/` — Superseded Getting Started Guides
- `QUICK_START_PHASE3.md` — Python-based Phase 3 quickstart (superseded by C++ guides)

### `testing_assets/` — Legacy Test Assets
3D model archives, texture packs, and development notes originally in `testing/`.

- `24-textures.zip` — Texture pack
- `99-intergalactic_spaceship-obj.rar` — Spaceship OBJ models
- `BlenderSpaceshipGenerator.zip` — Blender spaceship generator
- `CruiserBattleshipModulePack.zip` — Cruiser/battleship module pack
- `ModularShipModulePack.zip` — Modular ship module pack
- `qy0sx26192io-VulcanDkyrClass.zip` — Vulcan Dkyr class models
- `ideas and improvements.txt` — Informal development notes
- `serverbuildissues.txt` — Server build troubleshooting notes

### `python/` — Legacy Python Prototype
The original Python implementation before the project migrated to C++.
- `client/` — Original text/GUI client (pygame-based)
- `server/` — Original Python game server
- `engine/` — Core game engine (Python)
- `client_3d/` — 3D client prototype (Panda3D-based)
- `tests/` — Python test files
- `tests_suite/` — Additional test suite
- `demos/` — Demo and showcase scripts
- Build scripts and dependencies

### `design_docs/` — Original Design Documents
Original brainstorming and design specification files that have been fully merged
into the engine and codebase. Kept for historical reference.
- `1111.txt` — Initial ChatGPT design session (Atlas purpose, architecture)
- `1112.md` — Continuation of design session (graph types, AI, conversation system)
- `1114.txt` — Further design session (conversation engine, NPC knowledge graphs)
- `2222` — Extended design session (same series as 1112/1114)
- `atlas_plans_for_future.txt` — Future plans for Atlas (warp visuals, camera, HUD)
- `2d_implementation.txt` — 2D implementation notes (EVE warp cinematic breakdown)
- `features1.md` — Feature list and implementation notes
- `atlasUI.rtf` — UI specification document

### `legacy/` — Deprecated Project Files
- `eve baseline.rtf` — Original design baseline document
- `scopefor projectgui.rtf` — Early GUI scope document
- `scopeforprojectsofar.rtf` — Historical project scope notes
- `eve_online_manual.pdf` — External reference manual
- `rename_mapping.py` — Content renaming utility (ships, factions, etc.)
- `SESSION_SUMMARY.md` — Development session summary
- `QUICKSTART_VISUALS.md` — Visual quick-start guide (superseded by main README)

---

## Active Code

The active Atlas implementation lives in the repository root:
- `engine/` — Atlas Engine (C++20, game-agnostic, 17+ modules)
- `editor/` — Atlas Editor (authoring tool)
- `runtime/` — Atlas Runtime (standalone executable)
- `cpp_client/` — EVEOFFLINE game client (C++ / OpenGL)
- `cpp_server/` — EVEOFFLINE dedicated server
- `atlas_tests/` — Engine unit tests
- `data/` — Moddable game content (JSON)
- `schemas/` — Versioned project schemas
- `projects/` — Game projects (.atlas files)
- `tools/` — Modding utilities
- `scripts/` — Build scripts
- `docs/` — Active documentation
