#!/bin/bash
# EVEOFFLINE — Project Build Script
# Builds game client and server.
#
# Usage:
#   ./build_project.sh                    # Build everything (Release)
#   ./build_project.sh Debug              # Build everything (Debug)
#   ./build_project.sh Release client     # Build client only
#   ./build_project.sh Release server     # Build server only
#   ./build_project.sh Release test       # Build and run all tests
#
# Targets:
#   all      — Client + Server (default)
#   client   — EVEOFFLINE game client (OpenGL)
#   server   — EVEOFFLINE dedicated server
#   test     — Build and run all tests
#   validate — Validate project structure only

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$PROJECT_DIR"

# ── Configuration ──────────────────────────────────────────────

BUILD_TYPE="${1:-Release}"
TARGET="${2:-all}"
BUILD_DIR="build"
NPROC=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)

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

banner "EVEOFFLINE — Project Build ($BUILD_TYPE / $TARGET)"

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

# ── Build target ───────────────────────────────────────────────

build_client() {
    mkdir -p cpp_client/build
    cd cpp_client/build

    echo "Configuring client CMake ($BUILD_TYPE)..."
    cmake .. -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DUSE_SYSTEM_LIBS=ON

    echo "Building client..."
    cmake --build . --config "$BUILD_TYPE" -j"$NPROC"

    if [ $? -eq 0 ]; then
        echo "  ✓ Client build succeeded"
    else
        banner "CLIENT BUILD FAILED"
        exit 1
    fi

    cd "$PROJECT_DIR"
}

build_server() {
    mkdir -p cpp_server/build
    cd cpp_server/build

    echo "Configuring server CMake ($BUILD_TYPE)..."
    cmake .. -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DUSE_STEAM_SDK=OFF

    echo "Building server..."
    cmake --build . --config "$BUILD_TYPE" -j"$NPROC"

    if [ $? -eq 0 ]; then
        echo "  ✓ Server build succeeded"
    else
        banner "SERVER BUILD FAILED"
        exit 1
    fi

    cd "$PROJECT_DIR"
}

# ── Target dispatch ────────────────────────────────────────────

case "$TARGET" in
    all)
        banner "Building ALL targets (Client + Server)"
        build_client
        build_server
        ;;
    client)
        banner "Building Game Client"
        build_client
        ;;
    server)
        banner "Building Dedicated Server"
        build_server
        ;;
    test)
        banner "Building and Running Tests"

        echo "Running server tests..."
        mkdir -p cpp_server/build
        cd cpp_server/build
        cmake .. -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DBUILD_TESTS=ON -DUSE_STEAM_SDK=OFF
        cmake --build . --config "$BUILD_TYPE" --target test_systems -j"$NPROC"
        if [ -f bin/test_systems ]; then
            ./bin/test_systems
        fi
        cd "$PROJECT_DIR"
        ;;
    validate)
        banner "Validating Project"
        validate_project "projects/eveoffline"
        if [ $? -eq 0 ]; then
            banner "PROJECT VALID"
        else
            banner "VALIDATION FAILED"
            exit 1
        fi
        exit 0
        ;;
    *)
        echo "Unknown target: $TARGET"
        echo ""
        echo "Available targets: all, client, server, test, validate"
        exit 1
        ;;
esac

# ── Summary ────────────────────────────────────────────────────

banner "BUILD COMPLETE"

echo "Build type: $BUILD_TYPE"
echo "Target:     $TARGET"
echo ""

echo "Next steps:"
echo "  ./scripts/build_project.sh $BUILD_TYPE validate   # Validate project structure"
echo "  ./scripts/build_project.sh $BUILD_TYPE test        # Run all tests"
echo ""
