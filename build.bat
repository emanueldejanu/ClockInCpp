@echo off
REM Simple build script for ClockNet C++
REM Requires Visual Studio or Visual Studio Build Tools

echo Building ClockNet C++ Demo...

if not exist build mkdir build
cd build

cmake .. -G "Visual Studio 17 2022" -A x64

if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed!
    cd ..
    pause
    exit /b 1
)

cmake --build . --config Release

if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    cd ..
    pause
    exit /b 1
)

echo.
echo Build successful!
echo Executable: build\Release\ClockNetCpp.exe
echo.

cd ..
pause
