#!/bin/bash
# Atlas — Project Build Script
# Builds engine, dev client, and server according to Atlas project guidelines.
#
# Usage:
#   ./build_project.sh                    # Build everything (Release)
#   ./build_project.sh Debug              # Build everything (Debug)
#   ./build_project.sh Release engine     # Build engine only
#   ./build_project.sh Release client     # Build client only
#   ./build_project.sh Release server     # Build server only
#   ./build_project.sh Release test       # Build and run all tests
#
# Targets:
#   all      — Engine + Client + Server (default)
#   engine   — Atlas Engine static library
#   client   — EVE-Offline game client (OpenGL)
#   server   — EVE-Offline dedicated server
#   editor   — Atlas Editor
#   runtime  — Atlas Runtime
#   test     — Build and run all tests
#   validate — Validate project structure only

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

# ── Configuration ──────────────────────────────────────────────

BUILD_TYPE="${1:-Release}"
TARGET="${2:-all}"
BUILD_DIR="build"
NPROC=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# ── Helper functions ───────────────────────────────────────────

banner() {
    echo ""
    echo "================================================"
    echo "  $1"
    echo "================================================"
    echo ""
}

check_tool() {
    if ! command -v "$1" &> /dev/null; then
        echo "ERROR: $1 not found!"
        echo "$2"
        exit 1
    fi
}

# ── Dependency checks ─────────────────────────────────────────

banner "Atlas — Project Build ($BUILD_TYPE / $TARGET)"

check_tool cmake "Please install CMake from https://cmake.org/download/"

if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
    echo "ERROR: No C++ compiler found!"
    echo "Install build-essential (Linux) or Xcode (macOS)"
    exit 1
fi

# ── Validate project structure ─────────────────────────────────

validate_project() {
    local project_dir="$1"
    local errors=0

    echo "Validating project: $project_dir"

    # Check for .atlas manifest
    local atlas_count
    atlas_count=$(find "$project_dir" -maxdepth 1 -name "*.atlas" | wc -l)
    if [ "$atlas_count" -eq 0 ]; then
        echo "  ✗ Missing .atlas manifest file"
        errors=$((errors + 1))
    elif [ "$atlas_count" -gt 1 ]; then
        echo "  ✗ Multiple .atlas manifest files (exactly one required)"
        errors=$((errors + 1))
    else
        echo "  ✓ .atlas manifest found"
    fi

    # Check required directories
    for dir in worlds assets data; do
        if [ -d "$project_dir/$dir" ]; then
            echo "  ✓ $dir/ directory"
        else
            echo "  ✗ Missing $dir/ directory"
            errors=$((errors + 1))
        fi
    done

    # Check optional directories (report but don't fail)
    for dir in strategy ai config Code Schemas Tests conversations; do
        if [ -d "$project_dir/$dir" ]; then
            echo "  ✓ $dir/ directory (optional)"
        fi
    done

    # Check Plugin.toml if present
    if [ -f "$project_dir/Plugin.toml" ]; then
        echo "  ✓ Plugin.toml"
    fi

    if [ "$errors" -gt 0 ]; then
        echo ""
        echo "  $errors error(s) found. See docs/PROJECT_GUIDELINES.md for rules."
        return 1
    fi

    echo "  Project structure is valid."
    return 0
}

# ── CMake configure ────────────────────────────────────────────

configure_cmake() {
    local engine_flag="$1"
    local editor_flag="$2"
    local runtime_flag="$3"
    local tests_flag="$4"
    local client_flag="$5"
    local server_flag="$6"

    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"

    echo "Configuring CMake ($BUILD_TYPE)..."
    cmake .. -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
        -DBUILD_ATLAS_ENGINE="$engine_flag" \
        -DBUILD_ATLAS_EDITOR="$editor_flag" \
        -DBUILD_ATLAS_RUNTIME="$runtime_flag" \
        -DBUILD_ATLAS_TESTS="$tests_flag" \
        -DBUILD_CLIENT="$client_flag" \
        -DBUILD_SERVER="$server_flag" \
        -DUSE_SYSTEM_LIBS=ON

    if [ $? -ne 0 ]; then
        banner "CMAKE CONFIGURATION FAILED"
        echo "Install dependencies:"
        echo "  Ubuntu/Debian: sudo apt-get install libgl1-mesa-dev libglew-dev libglfw3-dev libglm-dev nlohmann-json3-dev libopenal-dev"
        echo "  macOS: brew install glfw glm glew nlohmann-json openal-soft"
        exit 1
    fi

    cd "$SCRIPT_DIR"
}

# ── Build target ───────────────────────────────────────────────

build_target() {
    local target_name="$1"

    cd "$BUILD_DIR"

    echo "Building${target_name:+ $target_name}..."
    if [ -n "$target_name" ]; then
        cmake --build . --config "$BUILD_TYPE" --target "$target_name" -- -j"$NPROC"
    else
        cmake --build . --config "$BUILD_TYPE" -- -j"$NPROC"
    fi

    if [ $? -eq 0 ]; then
        echo "  ✓ Build succeeded${target_name:+ ($target_name)}"
    else
        banner "BUILD FAILED${target_name:+ ($target_name)}"
        exit 1
    fi

    cd "$SCRIPT_DIR"
}

# ── Target dispatch ────────────────────────────────────────────

case "$TARGET" in
    all)
        banner "Building ALL targets (Engine + Client + Server)"
        configure_cmake ON ON ON ON ON ON
        build_target ""
        ;;
    engine)
        banner "Building Atlas Engine"
        configure_cmake ON OFF OFF OFF OFF OFF
        build_target "AtlasEngine"
        ;;
    client)
        banner "Building Dev Client"
        configure_cmake ON OFF OFF OFF ON OFF
        build_target ""
        ;;
    server)
        banner "Building Dedicated Server"
        configure_cmake ON OFF OFF OFF OFF ON
        build_target ""
        ;;
    editor)
        banner "Building Atlas Editor"
        configure_cmake ON ON OFF OFF OFF OFF
        build_target "AtlasEditor"
        ;;
    runtime)
        banner "Building Atlas Runtime"
        configure_cmake ON OFF ON OFF OFF OFF
        build_target "AtlasRuntime"
        ;;
    test)
        banner "Building and Running Tests"
        configure_cmake ON OFF OFF ON OFF ON
        build_target ""

        echo ""
        echo "Running engine tests..."
        cd "$BUILD_DIR"
        if [ -f atlas_tests/AtlasTests ]; then
            ./atlas_tests/AtlasTests
        fi
        cd "$SCRIPT_DIR"

        echo ""
        echo "Running server tests..."
        mkdir -p cpp_server/build
        cd cpp_server/build
        cmake .. -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_TESTS=ON -DUSE_STEAM_SDK=OFF
        cmake --build . --config "$BUILD_TYPE" --target test_systems -j"$NPROC"
        if [ -f bin/test_systems ]; then
            ./bin/test_systems
        fi
        cd "$SCRIPT_DIR"
        ;;
    validate)
        banner "Validating Projects"
        valid=0
        for project_dir in projects/*/; do
            if [ -d "$project_dir" ]; then
                validate_project "$project_dir" || valid=1
                echo ""
            fi
        done
        if [ "$valid" -eq 0 ]; then
            banner "ALL PROJECTS VALID"
        else
            banner "VALIDATION FAILED"
            exit 1
        fi
        exit 0
        ;;
    *)
        echo "Unknown target: $TARGET"
        echo ""
        echo "Available targets: all, engine, client, server, editor, runtime, test, validate"
        exit 1
        ;;
esac

# ── Summary ────────────────────────────────────────────────────

banner "BUILD COMPLETE"

echo "Build type: $BUILD_TYPE"
echo "Target:     $TARGET"
echo ""

if [ -d "$BUILD_DIR/bin" ]; then
    echo "Executables:"
    find "$BUILD_DIR/bin" -type f -executable 2>/dev/null | head -10
fi

echo ""
echo "Next steps:"
echo "  ./build_project.sh $BUILD_TYPE validate   # Validate project structure"
echo "  ./build_project.sh $BUILD_TYPE test        # Run all tests"
echo ""
