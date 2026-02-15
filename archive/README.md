# Archive

This directory contains legacy and deprecated files from the Atlas project's earlier development stages. All code and documents here are kept for historical reference only.

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
Session notes from specific development work sessions. These are historical records
of individual sessions, not authoritative references.

- `SESSION_SUMMARY.md` — Phase 5 development session (Feb 2, 2026)
- `SESSION_SUMMARY_CONTINUE_NEXT_STEPS_FEB2026.md` — Repository analysis session (Feb 11, 2026)
- `SESSION_SUMMARY_GUI_PHASE7.md` — GUI Phase 7 rendering session (Feb 11, 2026)
- `SESSION_SUMMARY_NEXT_TASKS.md` — Phase review session (Feb 7, 2026)

> **Note:** Additional session files are in `docs/sessions/` and track ongoing
> development activity across all phases.

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
