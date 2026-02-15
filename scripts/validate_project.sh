#!/bin/bash
# Atlas — Project Portability Validator
# Checks whether a project folder under projects/ is self-contained and
# can be dragged and dropped into the Atlas repo's projects/ directory.
#
# Usage:
#   ./validate_project.sh projects/eveoffline
#   ./validate_project.sh projects/atlas-sample
#   ./validate_project.sh                          # Validate all projects

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR/.."

PASS=0
FAIL=0
WARN=0

pass() { echo "  ✓ $1"; PASS=$((PASS + 1)); }
fail() { echo "  ✗ $1"; FAIL=$((FAIL + 1)); }
warn() { echo "  ? $1"; WARN=$((WARN + 1)); }

validate_project() {
    local dir="$1"
    local name
    name="$(basename "$dir")"

    echo ""
    echo "── Validating: $name ──"

    # 1. .atlas manifest (exactly one)
    local atlas_files
    atlas_files=$(find "$dir" -maxdepth 1 -name "*.atlas" 2>/dev/null)
    local atlas_count
    atlas_count=$(echo "$atlas_files" | grep -c '.atlas$' 2>/dev/null || echo 0)

    if [ "$atlas_count" -eq 1 ]; then
        pass ".atlas manifest ($(basename $atlas_files))"
    elif [ "$atlas_count" -eq 0 ]; then
        fail "Missing .atlas manifest file"
    else
        fail "Multiple .atlas files (exactly one required)"
    fi

    # 2. Required directories
    for req_dir in worlds assets data; do
        if [ -d "$dir/$req_dir" ]; then
            pass "$req_dir/ directory"
        else
            fail "Missing $req_dir/ directory (required by Atlas guidelines)"
        fi
    done

    # 3. Optional directories (informational)
    for opt_dir in strategy ai config Code Schemas Tests conversations; do
        if [ -d "$dir/$opt_dir" ]; then
            pass "$opt_dir/ directory (optional)"
        fi
    done

    # 4. Plugin.toml (recommended for engine registration)
    if [ -f "$dir/Plugin.toml" ]; then
        pass "Plugin.toml"
    else
        warn "No Plugin.toml — recommended for engine registration"
    fi

    # 5. README.md (recommended for documentation)
    if [ -f "$dir/README.md" ]; then
        pass "README.md"
    else
        warn "No README.md — recommended for documentation"
    fi

    # 6. No absolute paths in .atlas file (check for drive letters or root paths in values)
    if [ "$atlas_count" -eq 1 ]; then
        if grep -qE '"[^"]*[A-Za-z]:\\\\' "$atlas_files" 2>/dev/null || \
           grep -qE '"\/[A-Za-z]' "$atlas_files" 2>/dev/null; then
            fail ".atlas file contains absolute paths (must be relative)"
        else
            pass ".atlas uses relative paths only"
        fi
    fi

    # 7. No symlinks (portability)
    local symlinks
    symlinks=$(find "$dir" -type l 2>/dev/null | head -5)
    if [ -z "$symlinks" ]; then
        pass "No symlinks (portable)"
    else
        fail "Contains symlinks (not portable across repos)"
        echo "       $symlinks"
    fi

    # 8. Self-containment — no references outside project dir
    if [ "$atlas_count" -eq 1 ]; then
        if grep -q '\.\./\.\.' "$atlas_files" 2>/dev/null; then
            warn ".atlas references parent directories (../../) — data may need to be bundled for full portability"
        else
            pass ".atlas is self-contained (no ../../ references)"
        fi
    fi

    # 9. Check data/manifest.json for external references
    if [ -f "$dir/data/manifest.json" ]; then
        if grep -q '\.\./\.\.' "$dir/data/manifest.json" 2>/dev/null; then
            warn "data/manifest.json references parent directories — shared data will need separate handling when porting"
        else
            pass "data/manifest.json is self-contained"
        fi
    fi
}

# ── Main ───────────────────────────────────────────────────────

echo "================================================"
echo "  Atlas — Project Portability Validator"
echo "================================================"

if [ -n "$1" ]; then
    # Validate specific project
    if [ -d "$1" ]; then
        validate_project "$1"
    else
        echo "ERROR: Directory not found: $1"
        exit 1
    fi
else
    # Validate all projects
    for project_dir in projects/*/; do
        if [ -d "$project_dir" ]; then
            validate_project "$project_dir"
        fi
    done
fi

echo ""
echo "── Summary ──"
echo "  Passed:   $PASS"
echo "  Failed:   $FAIL"
echo "  Warnings: $WARN"
echo ""

if [ "$FAIL" -gt 0 ]; then
    echo "RESULT: FAIL — Project(s) not portable. Fix errors above."
    echo "See docs/PROJECT_GUIDELINES.md and projects/README.md for rules."
    exit 1
elif [ "$WARN" -gt 0 ]; then
    echo "RESULT: PASS (with warnings) — Project(s) are structurally valid."
    echo "Warnings indicate areas that may need attention for full portability."
    exit 0
else
    echo "RESULT: PASS — Project(s) are fully portable and guideline-compliant."
    exit 0
fi
