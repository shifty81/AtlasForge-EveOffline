# EVEOFFLINE — Atlas Project

This is the EVEOFFLINE game project structured as an Atlas Engine project.

## Opening in Atlas Editor

1. Launch Atlas Editor
2. Select `eveoffline.atlas` from the project picker
3. The editor will mount this directory and load all modules

## Project Structure

```
eveoffline/
├── eveoffline.atlas       # Project manifest
├── worlds/                # WorldGraph files
│   └── galaxy.worldgraph  # Galaxy generation graph
├── strategy/              # StrategyGraph files
│   └── faction_ai.strategygraph
├── data/                  # Game content (ships, modules, skills, etc.)
├── assets/                # Models, textures, audio
└── README.md
```

## Game Data

The `data/` directory contains moddable JSON game content:
- Ships (frigates, cruisers, battleships, capitals)
- Modules (weapons, defensive, mining, utility)
- Skills
- Universe definitions (systems, stargates, stations)
- Fleet, missions, market, contracts, etc.

All game data is loaded by Atlas Engine via the project manifest.
