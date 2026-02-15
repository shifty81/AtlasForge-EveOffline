# Atlas Engine — Plugin & AI Sandboxing Policy

This document defines the non-negotiable sandboxing rules enforced by Atlas Engine.
All plugins, AI tools, and extensions must comply with these rules to be loadable.

---

## Core Philosophy

Atlas enforces:
- Determinism
- Safety
- Reproducibility
- Multiplayer correctness

No extension is trusted by default.

---

## Execution Domains

| Domain | Mutable | Code Allowed |
|--------|---------|--------------|
| Engine Core | ✅ | Atlas only |
| Editor | ✅ | Atlas + Plugins |
| Runtime | ❌ | Atlas only |
| Plugins | ❌ | Sandbox only |
| Mods | ❌ | Data-only |

---

## Forbidden Operations (Plugins & AI)

Plugins and AI tools MAY NOT:

- Spawn threads directly
- Access system time
- Use OS randomness
- Perform file I/O
- Access network APIs
- Mutate editor or runtime state directly
- Allocate unmanaged memory pools

Violations cause immediate unload.

---

## Allowed APIs

Plugins MAY:

- Register graph nodes
- Execute pure math
- Access injected deterministic RNG
- Request background tasks via Atlas thread pool
- Register editor UI panels (editor-only)

---

## Deterministic RNG

All randomness must come from Atlas-injected RNG:

```cpp
DeterministicRNG& rng;
```

Any other RNG usage is forbidden.

---

## Threading Rules

Plugins must use:

```cpp
Atlas::RunAsync(task);
```

Direct thread creation is forbidden.

---

## Forbidden Symbol List

The following symbols are scanned for in plugin binaries. Any match causes
rejection at load time and CI failure:

```
std::thread
pthread_create
CreateThread
rand
srand
random_device
mt19937
time
clock_gettime
QueryPerformanceCounter
socket
connect
send
recv
```

---

## Validation & Enforcement

Sandboxing is enforced via:

- Compile-time SDK limitations
- Binary symbol scanning
- Runtime guards
- Determinism unit tests
- CI validation

Non-compliant plugins are rejected.

---

## AI Authoring Sandbox

AI tools operate under the same restrictions as plugins and:

- Cannot execute runtime logic
- Cannot bypass schemas
- Cannot emit nondeterministic graphs

AI output is always validated before use.

---

## Zero Exceptions Policy

- There are no whitelisted plugins
- There are no privileged mods
- There are no runtime overrides

Atlas remains authoritative.

---

## Related Documents

- [Architecture](ARCHITECTURE.md) — Engine architecture overview
- [Atlas Naming Conventions](ATLAS_NAMING_CONVENTIONS.md) — Code style rules
- [Project Guidelines](docs/PROJECT_GUIDELINES.md) — Project structure rules
- [Atlas Simulation Philosophy](ATLAS_SIMULATION_PHILOSOPHY.md) — Simulation design
