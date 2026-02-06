@echo off
REM Build ClockNetCpp using MSBuild (Visual Studio)
echo Building ClockNetCpp with MSBuild...

REM Try to find MSBuild
set MSBUILD=""

REM Check for VS 2022
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" (
    set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
)
if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe" (
    set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe"
)
if exist "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe" (
    set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
)

if %MSBUILD%=="" (
    echo ERROR: Could not find MSBuild. Please install Visual Studio 2022.
    pause
    exit /b 1
)

echo Found MSBuild: %MSBUILD%
echo.

REM Build Release x64
echo Building Release x64...
%MSBUILD% ClockNetCpp.sln /p:Configuration=Release /p:Platform=x64 /m

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Build successful!
echo Executable: bin\x64\Release\ClockNetCpp.exe
echo.

REM Ask if user wants to run
set /p RUN="Run the application? (Y/N): "
if /i "%RUN%"=="Y" (
    start bin\x64\Release\ClockNetCpp.exe
)

pause
