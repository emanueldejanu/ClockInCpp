# ClockNet C++ Port

A complete C++ port of the ClockNet analog clock control from .NET to native Windows using Windows API and GDI+.

## Features

- **Reusable Windows Control**: ClockControl class that can be embedded in any Windows application
- **Shape-Based Architecture**: Extensible shape system for creating custom clock elements
- **Multiple Templates**: Pre-built clock templates (Black, Fancy, and more)
- **GDI+ Rendering**: High-quality anti-aliased graphics
- **Easy to Extend**: Add custom shapes and templates

## Project Structure

```
clock-cpp/
├── ClockControl.h/cpp          # Main reusable clock control
├── Shapes/
│   ├── IShape.h                # Shape interface
│   ├── ShapeBase.h/cpp         # Base shape implementation
│   ├── VectorialShapeBase.h/cpp # Base for vector shapes
│   ├── HandBase.h/cpp          # Base for clock hands
│   ├── VectorialHandBase.h/cpp # Base for vector hands
│   ├── Basic/
│   │   └── LineHand.h/cpp      # Simple line hand
│   ├── Default/
│   │   ├── FlatBackground.h/cpp     # Flat circular background
│   │   ├── DiamondHand.h/cpp        # Diamond-shaped hand
│   │   ├── Pin.h/cpp                # Center pin
│   │   ├── Ticks.h/cpp              # Clock ticks/marks
│   │   └── HourNumerals.h/cpp       # Hour numbers
│   └── Advanced/
│       └── FancyBackground.h/cpp    # Gradient background with rims
├── Templates/
│   ├── TemplateBase.h          # Template base class
│   ├── BlackTemplate.h/cpp     # Black-themed clock
│   └── FancyTemplate.h/cpp     # Fancy-themed clock
├── Utils/
│   └── ColorExtensions.h       # Color manipulation utilities
├── main.cpp                    # Demo application
├── CMakeLists.txt             # CMake build configuration
├── build.bat                  # Windows build script
└── README.md                  # This file
```

## Building

### Requirements

- Windows 10/11
- Visual Studio 2022 or Visual Studio Build Tools
- CMake 3.15 or higher

### Build Steps

#### Option 1: Using the build script (Easiest)

```batch
build.bat
```

#### Option 2: Manual CMake build

```batch
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

#### Option 3: Using Visual Studio

1. Open the folder in Visual Studio 2022
2. Visual Studio will automatically configure CMake
3. Press F5 to build and run

## Usage

### Using the Clock Control in Your Application

```cpp
#include "ClockControl.h"
#include "Templates/BlackTemplate.h"

// In your window creation code:
ClockNet::ClockControl* pClock = new ClockNet::ClockControl();
pClock->Create(hwndParent, 10, 10, 300, 300);

// Apply a template
ClockNet::Templates::BlackTemplate blackTemplate;
pClock->ApplyTemplate(&blackTemplate);

// The clock will automatically update every 100ms
```

### Creating Custom Shapes

```cpp
#include "Shapes/VectorialShapeBase.h"

class MyCustomShape : public ClockNet::Shapes::VectorialShapeBase {
protected:
    void OnDraw(ClockNet::Shapes::ClockDrawingContext& context) override {
        // Your custom drawing code using GDI+
        context.Graphics->FillEllipse(GetBrush(), -50, -50, 100, 100);
    }

public:
    MyCustomShape() {
        m_name = L"My Custom Shape";
        m_fillColor = Gdiplus::Color::Blue;
    }
};
```

### Creating Custom Templates

```cpp
#include "Templates/TemplateBase.h"

class MyTemplate : public ClockNet::TemplateBase {
protected:
    std::vector<std::shared_ptr<Shapes::IShape>> EnumerateShapes() override {
        std::vector<std::shared_ptr<Shapes::IShape>> shapes;

        // Add your custom shapes
        auto background = std::make_shared<Shapes::Default::FlatBackground>();
        background->SetFillColor(Gdiplus::Color::Blue);
        shapes.push_back(background);

        // Add more shapes...

        return shapes;
    }
};
```

## Implemented Shapes

### Backgrounds
- **FlatBackground**: Simple circular background
- **FancyBackground**: Gradient background with decorative rims

### Hands
- **LineHand**: Simple line hand
- **DiamondHand**: Diamond-shaped hand

### Rim Elements
- **Ticks**: Clock tick marks around the rim
- **HourNumerals**: Hour numbers (1-12)

### Other
- **Pin**: Center pin that holds the hands

## Implemented Templates

1. **BlackTemplate**: Black background with fancy gradient, colored hands
2. **FancyTemplate**: White background with elegant design

## Original Project

This is a C++ port of the original ClockNet project:
- Original: https://github.com/lastunicorn/ClockNet
- Original Author: Dust in the Wind
- License: GPL v3

## License

GPL v3 - Same as the original project

## Additional Templates from Original Project

The original .NET project includes these templates that can be ported:
- BlueTemplate
- GothicTemplate
- PandaTemplate
- ShadowHandsTemplate
- SunTemplate
- WhiteFancyTemplate

## TODO

- Port additional shapes (NibHand, CapsuleHand, DigitalHand, DotHand, FancySweepHand, SlotHand)
- Port additional templates (Blue, Gothic, Panda, ShadowHands, Sun, WhiteFancy)
- Implement movement/time providers
- Add image-based shapes
- Add string-based shapes
- Implement shape serialization

## Contributing

Feel free to extend this project by:
- Adding more shapes
- Creating new templates
- Improving performance
- Adding features

## Contact

For questions or issues, please refer to the original ClockNet project.
