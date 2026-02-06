# Building with Visual Studio 2022

## Quick Start

### Option 1: Double-click to open
Simply double-click `ClockNetCpp.sln` to open the project in Visual Studio 2022.

### Option 2: From Visual Studio
1. Open Visual Studio 2022
2. Click "Open a project or solution"
3. Navigate to `C:\Work\Playground\clock-cpp`
4. Select `ClockNetCpp.sln`

## Building the Project

### Using the Menu
1. Select **Build → Build Solution** (or press `Ctrl+Shift+B`)
2. Wait for the build to complete
3. The executable will be in `bin\x64\Debug\ClockNetCpp.exe` or `bin\x64\Release\ClockNetCpp.exe`

### Using the Toolbar
1. Select the build configuration:
   - **Debug** for debugging with symbols
   - **Release** for optimized production build

2. Select the platform:
   - **x64** (recommended for modern systems)
   - **x86** (for 32-bit compatibility)

3. Click the **Build** button or press `F7`

## Running the Project

### Debug Mode
1. Press `F5` or click **Debug → Start Debugging**
2. This will build (if needed) and run with debugger attached
3. You can set breakpoints by clicking in the left margin of code

### Release Mode
1. Change configuration to **Release**
2. Press `Ctrl+F5` or click **Debug → Start Without Debugging**
3. This runs the optimized version without debugger

## Project Structure in Solution Explorer

```
ClockNetCpp
├── Source Files
│   ├── main.cpp                    # Demo application entry point
│   └── ClockControl.cpp            # Main control implementation
├── Header Files
│   └── ClockControl.h
├── Shapes
│   ├── IShape.h
│   ├── ClockDrawingContext.h
│   ├── ShapeBase.cpp/.h
│   ├── VectorialShapeBase.cpp/.h
│   ├── HandBase.cpp/.h
│   ├── VectorialHandBase.cpp/.h
│   ├── TimeComponent.h
│   ├── Basic
│   │   └── LineHand.cpp/.h
│   ├── Default
│   │   ├── FlatBackground.cpp/.h
│   │   ├── DiamondHand.cpp/.h
│   │   ├── Pin.cpp/.h
│   │   ├── Ticks.cpp/.h
│   │   └── HourNumerals.cpp/.h
│   └── Advanced
│       └── FancyBackground.cpp/.h
├── Templates
│   ├── TemplateBase.h
│   ├── BlackTemplate.cpp/.h
│   └── FancyTemplate.cpp/.h
├── Utils
│   └── ColorExtensions.h
└── Documentation
    ├── README.md
    ├── QUICKSTART.md
    ├── IMPLEMENTATION_STATUS.md
    ├── CMakeLists.txt
    └── build.bat
```

## Build Configurations

### Debug Configuration
- **Purpose**: Development and debugging
- **Optimizations**: Disabled
- **Debug Info**: Full
- **Output**: `bin\x64\Debug\ClockNetCpp.exe`
- **Size**: Larger (includes debug symbols)
- **Performance**: Slower

### Release Configuration
- **Purpose**: Production/distribution
- **Optimizations**: Maximum (`/O2`)
- **Debug Info**: Minimal (for crash reports)
- **Output**: `bin\x64\Release\ClockNetCpp.exe`
- **Size**: Smaller
- **Performance**: Faster

## Keyboard Shortcuts

| Action | Shortcut |
|--------|----------|
| Build Solution | `Ctrl+Shift+B` |
| Start Debugging | `F5` |
| Start Without Debugging | `Ctrl+F5` |
| Toggle Breakpoint | `F9` |
| Step Over | `F10` |
| Step Into | `F11` |
| Find in Files | `Ctrl+Shift+F` |
| Go to Definition | `F12` |
| Build Current Project | `Ctrl+B` |
| Rebuild Solution | `Ctrl+Alt+F7` |

## Common Issues and Solutions

### Issue: Cannot open source file
**Solution**: Make sure all files are in the correct directories relative to the `.sln` file.

### Issue: LNK2019 Unresolved external symbol
**Solution**:
1. Check that all `.cpp` files are included in the project
2. Verify that `gdiplus.lib` and `comctl32.lib` are linked
3. Clean and rebuild: **Build → Clean Solution**, then **Build → Rebuild Solution**

### Issue: Cannot find Windows SDK
**Solution**:
1. Go to **Project → Properties**
2. Under **General**, set **Windows SDK Version** to your installed version
3. If no SDK is installed, install it via **Visual Studio Installer → Modify → Individual Components → Windows 10/11 SDK**

### Issue: Platform Toolset not found
**Solution**: The project uses `v143` (VS 2022). If you have a different version:
1. Right-click project in Solution Explorer
2. Select **Properties**
3. Go to **Configuration Properties → General**
4. Change **Platform Toolset** to your installed version

### Issue: Can't open .sln file
**Solution**:
- Make sure you have Visual Studio 2022 installed
- If you have VS 2019, you may need to update the solution file format
- Or use the CMake build method instead

## Customizing Build Settings

### Changing Output Directory
1. Right-click project → **Properties**
2. Go to **Configuration Properties → General**
3. Modify **Output Directory**
4. Current setting: `$(SolutionDir)bin\$(Platform)\$(Configuration)\`

### Adding Include Directories
1. Right-click project → **Properties**
2. Go to **C/C++ → General**
3. Edit **Additional Include Directories**

### Linking Additional Libraries
1. Right-click project → **Properties**
2. Go to **Linker → Input**
3. Edit **Additional Dependencies**

## IntelliSense

Visual Studio provides IntelliSense (code completion):
- **Auto-completion**: Start typing and press `Ctrl+Space`
- **Parameter info**: Type `(` after a function name
- **Quick info**: Hover over any symbol
- **Go to definition**: `F12` or `Ctrl+Click` on symbol

## Debugging Features

### Setting Breakpoints
1. Click in the left margin of a code line
2. Red dot appears indicating breakpoint
3. When debugging (F5), execution stops at breakpoint

### Watch Variables
1. While debugging, hover over variables to see values
2. Right-click variable → **Add Watch**
3. View in **Watch** window

### Call Stack
- View in **Debug → Windows → Call Stack** (`Ctrl+Alt+C`)
- Shows function call hierarchy

### Output Window
- View compilation output
- **View → Output** (`Ctrl+Alt+O`)

## Multi-Configuration Building

To build all configurations at once:
1. **Build → Batch Build**
2. Check the configurations you want to build
3. Click **Build**

## Clean Build

Sometimes you need to clean and rebuild:
1. **Build → Clean Solution** (removes all build artifacts)
2. **Build → Rebuild Solution** (clean + build)

This helps resolve build issues after changes.

## Git Integration

Visual Studio has built-in Git support:
- View changes: **View → Git Changes**
- Commit: Enter message and click **Commit All**
- Push/Pull: Use toolbar buttons
- View history: **View → Git Repository**

## Performance Profiling

To profile the application:
1. **Debug → Performance Profiler** (`Alt+F2`)
2. Select profiling tools (CPU Usage, Memory Usage)
3. Start profiling
4. Use the application
5. Stop profiling to see results

## Publishing

To create a distributable build:
1. Build in **Release** configuration
2. The executable is in `bin\x64\Release\ClockNetCpp.exe`
3. Include with your distribution:
   - `ClockNetCpp.exe`
   - `gdiplus.dll` (if not on target system)
   - Any other required DLLs

Note: Most Windows 10/11 systems already have GDI+ installed.

## System Requirements

- **Visual Studio**: 2022 (17.0 or later)
- **Windows SDK**: 10.0 or later
- **Platform Toolset**: v143
- **C++ Standard**: C++17
- **Minimum Windows**: Windows 10

## Support

For issues specific to:
- **Building**: Check this document
- **Using the control**: See `QUICKSTART.md`
- **Features**: See `README.md` and `IMPLEMENTATION_STATUS.md`

## Next Steps

After building successfully:
1. Read `QUICKSTART.md` for usage examples
2. Explore the code in Visual Studio
3. Try modifying shapes or creating new templates
4. Use the debugger to understand how it works

Happy coding! 🎨⏰
