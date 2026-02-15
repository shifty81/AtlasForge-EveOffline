# EVEOFFLINE — Atlas Project

This directory contains the EVEOFFLINE game as an
[Atlas Engine](https://github.com/shifty81/Atlas) project.

## Project

| Project | Description |
|---------|-------------|
| `eveoffline/` | PVE space simulator game project |

## Project Structure

```
eveoffline/
├── eveoffline.atlas       # Project manifest (required)
├── Plugin.toml            # Plugin descriptor
├── README.md              # Project documentation
├── worlds/                # WorldGraph files
├── strategy/              # StrategyGraph files
├── conversations/         # ConversationGraph files
├── data/                  # Game content manifest
├── assets/                # Models, textures, audio
├── config/                # Runtime configuration
├── Code/                  # Game-specific code
├── Schemas/               # Data validation schemas
├── Tests/                 # Project tests
└── ai/                    # AI rules and knowledge graphs
```

See [PROJECT_GUIDELINES.md](../docs/PROJECT_GUIDELINES.md) for complete rules.

## Portability — Drag and Drop to Atlas Repo

The `eveoffline/` project is designed to be **portable** — you can copy it
into the [Atlas repo's](https://github.com/shifty81/Atlas) `projects/` directory
and it should work with the Atlas Editor.

### How to Port to Atlas Repo

```bash
# Copy project folder to Atlas repo
cp -r projects/eveoffline /path/to/Atlas/projects/

# Validate it works
cd /path/to/Atlas
./scripts/validate_project.sh projects/eveoffline
```

### Validate Before Porting

```bash
./scripts/validate_project.sh projects/eveoffline
```

## Building

```bash
./scripts/build_project.sh Release client     # Build game client
./scripts/build_project.sh Release server     # Build dedicated server
./scripts/build_project.sh Release test       # Build and run all tests
./scripts/build_project.sh Release validate   # Validate project structure
```
