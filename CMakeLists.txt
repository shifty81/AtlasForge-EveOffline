# Atlas - Root CMakeLists.txt
# Unified build: Atlas Engine core + EVEOFFLINE game project (client & server)
#
# Architecture:
#   engine/       → AtlasEngine static library (generic, game-agnostic)
#   editor/       → AtlasEditor executable (authoring tool)
#   cpp_client/   → EVEOFFLINE game client (links AtlasEngine)
#   cpp_server/   → EVEOFFLINE game server (links AtlasEngine)
#   atlas_tests/  → Atlas engine unit tests

cmake_minimum_required(VERSION 3.15)
project(Atlas VERSION 1.0.0 LANGUAGES C CXX)

# Set C++ standard (C++20 to match Atlas Engine requirements)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_CLIENT "Build C++ OpenGL client" ON)
option(BUILD_SERVER "Build C++ dedicated server" ON)
option(BUILD_ATLAS_ENGINE "Build Atlas Engine library" ON)
option(BUILD_ATLAS_EDITOR "Build Atlas Editor" OFF)
option(BUILD_ATLAS_RUNTIME "Build Atlas Runtime" OFF)
option(BUILD_ATLAS_TESTS "Build Atlas Engine tests" ON)

# --- Atlas Engine (core library) ---
if(BUILD_ATLAS_ENGINE)
    message(STATUS "Adding Atlas Engine library...")
    add_subdirectory(engine)
endif()

# --- Atlas Editor ---
if(BUILD_ATLAS_EDITOR AND BUILD_ATLAS_ENGINE)
    message(STATUS "Adding Atlas Editor...")
    add_subdirectory(editor)
endif()

# --- Atlas Runtime ---
if(BUILD_ATLAS_RUNTIME AND BUILD_ATLAS_ENGINE)
    message(STATUS "Adding Atlas Runtime...")
    add_subdirectory(runtime)
endif()

# --- Atlas Engine Tests ---
if(BUILD_ATLAS_TESTS AND BUILD_ATLAS_ENGINE)
    enable_testing()
    message(STATUS "Adding Atlas Engine tests...")
    add_subdirectory(atlas_tests)
endif()

# --- EVEOFFLINE Game Client ---
if(BUILD_CLIENT)
    message(STATUS "Adding C++ Client to solution...")
    add_subdirectory(cpp_client)
endif()

# --- EVEOFFLINE Game Server ---
if(BUILD_SERVER)
    message(STATUS "Adding C++ Server to solution...")
    add_subdirectory(cpp_server)
endif()

message(STATUS "")
message(STATUS "Atlas Configuration:")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Atlas Engine:  ${BUILD_ATLAS_ENGINE}")
message(STATUS "  Atlas Editor:  ${BUILD_ATLAS_EDITOR}")
message(STATUS "  Atlas Runtime: ${BUILD_ATLAS_RUNTIME}")
message(STATUS "  Atlas Tests:   ${BUILD_ATLAS_TESTS}")
message(STATUS "  Game Client:   ${BUILD_CLIENT}")
message(STATUS "  Game Server:   ${BUILD_SERVER}")
message(STATUS "")
message(STATUS "After generation, open the solution file in Visual Studio:")
message(STATUS "  build_vs/Atlas.sln")
message(STATUS "")
