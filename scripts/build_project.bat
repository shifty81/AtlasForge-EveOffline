@echo off
REM EVEOFFLINE — Project Build Script (Windows)
REM Builds game client and server.
REM
REM Usage:
REM   build_project.bat                    # Build everything (Release)
REM   build_project.bat Debug              # Build everything (Debug)
REM   build_project.bat Release client     # Build client only
REM   build_project.bat Release server     # Build server only
REM   build_project.bat Release test       # Build and run all tests
REM
REM Targets:
REM   all      — Client + Server (default)
REM   client   — EVEOFFLINE game client (OpenGL)
REM   server   — EVEOFFLINE dedicated server
REM   test     — Build and run all tests
REM   validate — Validate project structure only

setlocal enabledelayedexpansion

set "SCRIPT_DIR=%~dp0"
cd /d "%SCRIPT_DIR%\.."

set "BUILD_TYPE=%~1"
if "%BUILD_TYPE%"=="" set "BUILD_TYPE=Release"

set "TARGET=%~2"
if "%TARGET%"=="" set "TARGET=all"

echo.
echo ================================================
echo   EVEOFFLINE — Project Build (%BUILD_TYPE% / %TARGET%)
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
if /i "%TARGET%"=="client" goto :build_client
if /i "%TARGET%"=="server" goto :build_server
if /i "%TARGET%"=="test" goto :build_test
if /i "%TARGET%"=="validate" goto :validate

echo Unknown target: %TARGET%
echo.
echo Available targets: all, client, server, test, validate
exit /b 1

:build_all
echo Building ALL targets (Client + Server)...
if not exist "cpp_client\build" mkdir "cpp_client\build"
cd "cpp_client\build"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DUSE_SYSTEM_LIBS=ON
if %ERRORLEVEL% neq 0 goto :cmake_fail
cmake --build . --config %BUILD_TYPE%
if %ERRORLEVEL% neq 0 goto :build_fail
cd /d "%SCRIPT_DIR%\.."

if not exist "cpp_server\build" mkdir "cpp_server\build"
cd "cpp_server\build"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DUSE_STEAM_SDK=OFF
if %ERRORLEVEL% neq 0 goto :cmake_fail
cmake --build . --config %BUILD_TYPE%
if %ERRORLEVEL% neq 0 goto :build_fail
cd /d "%SCRIPT_DIR%\.."
goto :success

:build_client
echo Building Game Client...
if not exist "cpp_client\build" mkdir "cpp_client\build"
cd "cpp_client\build"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DUSE_SYSTEM_LIBS=ON
if %ERRORLEVEL% neq 0 goto :cmake_fail
cmake --build . --config %BUILD_TYPE%
if %ERRORLEVEL% neq 0 goto :build_fail
cd /d "%SCRIPT_DIR%\.."
goto :success

:build_server
echo Building Dedicated Server...
if not exist "cpp_server\build" mkdir "cpp_server\build"
cd "cpp_server\build"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DUSE_STEAM_SDK=OFF
if %ERRORLEVEL% neq 0 goto :cmake_fail
cmake --build . --config %BUILD_TYPE%
if %ERRORLEVEL% neq 0 goto :build_fail
cd /d "%SCRIPT_DIR%\.."
goto :success

:build_test
echo Building and Running Tests...
echo.
echo Running server tests...
if not exist "cpp_server\build" mkdir "cpp_server\build"
cd "cpp_server\build"
cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_TESTS=ON -DUSE_STEAM_SDK=OFF
cmake --build . --config %BUILD_TYPE% --target test_systems
if exist "bin\%BUILD_TYPE%\test_systems.exe" (
    "bin\%BUILD_TYPE%\test_systems.exe"
)
cd /d "%SCRIPT_DIR%\.."
goto :success

:validate
echo Validating Project...
set "valid=0"
for /d %%D in (projects\eveoffline) do (
    echo Validating project: %%D
    if exist "%%D\*.atlas" (
        echo   OK .atlas manifest found
    ) else (
        echo   X Missing .atlas manifest file
        set "valid=1"
    )
    if exist "%%D\worlds" (echo   OK worlds/ directory) else (echo   X Missing worlds/ directory & set "valid=1")
    if exist "%%D\assets" (echo   OK assets/ directory) else (echo   X Missing assets/ directory & set "valid=1")
    if exist "%%D\data"   (echo   OK data/ directory)   else (echo   X Missing data/ directory   & set "valid=1")
    echo.
)
if !valid!==0 (
    echo PROJECT VALID
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
cd /d "%SCRIPT_DIR%\.."
exit /b 1

:build_fail
echo.
echo ================================================
echo   BUILD FAILED
echo ================================================
cd /d "%SCRIPT_DIR%\.."
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
echo   scripts\build_project.bat %BUILD_TYPE% validate   # Validate project structure
echo   scripts\build_project.bat %BUILD_TYPE% test        # Run all tests
echo.
exit /b 0
