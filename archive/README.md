# Archive

This directory contains legacy and deprecated files from the Atlas project's earlier development stages. All code and documents here are kept for historical reference only.

## Contents

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

### `design_docs/` — Merged Design Documents
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

## Active Code

The active Atlas implementation is in:
- `cpp_client/` — C++ OpenGL game client with Atlas UI
- `cpp_server/` — C++ dedicated game server
- `data/` — Game data (JSON configs)
