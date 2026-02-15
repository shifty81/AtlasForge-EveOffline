@echo off
REM Atlas — Project Build Script (Windows)
REM Builds engine, dev client, and server according to Atlas project guidelines.
REM
REM Usage:
REM   build_project.bat                    # Build everything (Release)
REM   build_project.bat Debug              # Build everything (Debug)
REM   build_project.bat Release engine     # Build engine only
REM   build_project.bat Release client     # Build client only
REM   build_project.bat Release server     # Build server only
REM   build_project.bat Release test       # Build and run all tests
REM
REM Targets:
REM   all      — Engine + Client + Server (default)
REM   engine   — Atlas Engine static library
REM   client   — EVE-Offline game client (OpenGL)
REM   server   — EVE-Offline dedicated server
REM   editor   — Atlas Editor
REM   runtime  — Atlas Runtime
REM   test     — Build and run all tests
REM   validate — Validate project structure only

setlocal enabledelayedexpansion

set "SCRIPT_DIR=%~dp0"
cd /d "%SCRIPT_DIR%"

set "BUILD_TYPE=%~1"
if "%BUILD_TYPE%"=="" set "BUILD_TYPE=Release"

set "TARGET=%~2"
if "%TARGET%"=="" set "TARGET=all"

set "BUILD_DIR=build"

echo.
echo ================================================
echo   Atlas — Project Build (%BUILD_TYPE% / %TARGET%)
echo ================================================
echo.

REM ── Check CMake ──────────────────────────────────────────────

where cmake >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake not found!
    echo Please install CMake from https://cmake.org/download/
    exit /b 1
)

REM ── Target dispatch ──────────────────────────────────────────

if /i "%TARGET%"=="all" goto :build_all
if /i "%TARGET%"=="engine" goto :build_engine
if /i "%TARGET%"=="client" goto :build_client
if /i "%TARGET%"=="server" goto :build_server
if /i "%TARGET%"=="editor" goto :build_editor
if /i "%TARGET%"=="runtime" goto :build_runtime
if /i "%TARGET%"=="test" goto :build_test
if /i "%TARGET%"=="validate" goto :validate

echo Unknown target: %TARGET%
echo.
echo Available targets: all, engine, client, server, editor, runtime, test, validate
exit /b 1

:build_all
echo Building ALL targets (Engine + Client + Server)...
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_ATLAS_ENGINE=ON -DBUILD_ATLAS_EDITOR=ON -DBUILD_ATLAS_RUNTIME=ON -DBUILD_ATLAS_TESTS=ON -DBUILD_CLIENT=ON -DBUILD_SERVER=ON
if %ERRORLEVEL% neq 0 goto :cmake_fail
cmake --build . --config %BUILD_TYPE%
if %ERRORLEVEL% neq 0 goto :build_fail
cd "%SCRIPT_DIR%"
goto :success

:build_engine
echo Building Atlas Engine...
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_ATLAS_ENGINE=ON -DBUILD_CLIENT=OFF -DBUILD_SERVER=OFF -DBUILD_ATLAS_TESTS=OFF -DBUILD_ATLAS_EDITOR=OFF -DBUILD_ATLAS_RUNTIME=OFF
if %ERRORLEVEL% neq 0 goto :cmake_fail
cmake --build . --config %BUILD_TYPE% --target AtlasEngine
if %ERRORLEVEL% neq 0 goto :build_fail
cd "%SCRIPT_DIR%"
goto :success

:build_client
echo Building Dev Client...
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_ATLAS_ENGINE=ON -DBUILD_CLIENT=ON -DBUILD_SERVER=OFF -DBUILD_ATLAS_TESTS=OFF -DBUILD_ATLAS_EDITOR=OFF -DBUILD_ATLAS_RUNTIME=OFF
if %ERRORLEVEL% neq 0 goto :cmake_fail
cmake --build . --config %BUILD_TYPE%
if %ERRORLEVEL% neq 0 goto :build_fail
cd "%SCRIPT_DIR%"
goto :success

:build_server
echo Building Dedicated Server...
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_ATLAS_ENGINE=ON -DBUILD_SERVER=ON -DBUILD_CLIENT=OFF -DBUILD_ATLAS_TESTS=OFF -DBUILD_ATLAS_EDITOR=OFF -DBUILD_ATLAS_RUNTIME=OFF
if %ERRORLEVEL% neq 0 goto :cmake_fail
cmake --build . --config %BUILD_TYPE%
if %ERRORLEVEL% neq 0 goto :build_fail
cd "%SCRIPT_DIR%"
goto :success

:build_editor
echo Building Atlas Editor...
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_ATLAS_ENGINE=ON -DBUILD_ATLAS_EDITOR=ON -DBUILD_CLIENT=OFF -DBUILD_SERVER=OFF -DBUILD_ATLAS_TESTS=OFF -DBUILD_ATLAS_RUNTIME=OFF
if %ERRORLEVEL% neq 0 goto :cmake_fail
cmake --build . --config %BUILD_TYPE% --target AtlasEditor
if %ERRORLEVEL% neq 0 goto :build_fail
cd "%SCRIPT_DIR%"
goto :success

:build_runtime
echo Building Atlas Runtime...
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_ATLAS_ENGINE=ON -DBUILD_ATLAS_RUNTIME=ON -DBUILD_CLIENT=OFF -DBUILD_SERVER=OFF -DBUILD_ATLAS_TESTS=OFF -DBUILD_ATLAS_EDITOR=OFF
if %ERRORLEVEL% neq 0 goto :cmake_fail
cmake --build . --config %BUILD_TYPE% --target AtlasRuntime
if %ERRORLEVEL% neq 0 goto :build_fail
cd "%SCRIPT_DIR%"
goto :success

:build_test
echo Building and Running Tests...
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_ATLAS_ENGINE=ON -DBUILD_ATLAS_TESTS=ON -DBUILD_CLIENT=OFF -DBUILD_SERVER=ON
if %ERRORLEVEL% neq 0 goto :cmake_fail
cmake --build . --config %BUILD_TYPE%
if %ERRORLEVEL% neq 0 goto :build_fail
cd "%SCRIPT_DIR%"
echo.
echo Running engine tests...
if exist "%BUILD_DIR%\atlas_tests\%BUILD_TYPE%\AtlasTests.exe" (
    "%BUILD_DIR%\atlas_tests\%BUILD_TYPE%\AtlasTests.exe"
)
echo.
echo Running server tests...
if not exist "cpp_server\build" mkdir "cpp_server\build"
cd "cpp_server\build"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_TESTS=ON -DUSE_STEAM_SDK=OFF
cmake --build . --config %BUILD_TYPE% --target test_systems
if exist "bin\%BUILD_TYPE%\test_systems.exe" (
    "bin\%BUILD_TYPE%\test_systems.exe"
)
cd "%SCRIPT_DIR%"
goto :success

:validate
echo Validating Projects...
set "valid=0"
for /d %%D in (projects\*) do (
    echo Validating project: %%D
    set "atlas_found=0"
    for %%F in (%%D\*.atlas) do set "atlas_found=1"
    if !atlas_found!==0 (
        echo   X Missing .atlas manifest file
        set "valid=1"
    ) else (
        echo   OK .atlas manifest found
    )
    if exist "%%D\worlds" (echo   OK worlds/ directory) else (echo   X Missing worlds/ directory & set "valid=1")
    if exist "%%D\assets" (echo   OK assets/ directory) else (echo   X Missing assets/ directory & set "valid=1")
    if exist "%%D\data"   (echo   OK data/ directory)   else (echo   X Missing data/ directory   & set "valid=1")
    echo.
)
if !valid!==0 (
    echo ALL PROJECTS VALID
) else (
    echo VALIDATION FAILED
    exit /b 1
)
exit /b 0

:cmake_fail
echo.
echo ================================================
echo   CMAKE CONFIGURATION FAILED
echo ================================================
cd "%SCRIPT_DIR%"
exit /b 1

:build_fail
echo.
echo ================================================
echo   BUILD FAILED
echo ================================================
cd "%SCRIPT_DIR%"
exit /b 1

:success
echo.
echo ================================================
echo   BUILD COMPLETE
echo ================================================
echo.
echo Build type: %BUILD_TYPE%
echo Target:     %TARGET%
echo.
echo Next steps:
echo   build_project.bat %BUILD_TYPE% validate   # Validate project structure
echo   build_project.bat %BUILD_TYPE% test        # Run all tests
echo.
exit /b 0
