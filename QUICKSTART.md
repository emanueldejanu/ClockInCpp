## Quick Start Guide

### 1. Build the Project

```batch
cd C:\Work\Playground\clock-cpp
build.bat
```

This will:
- Create a `build` folder
- Configure CMake with Visual Studio 2022
- Build the Release version
- Create `build\Release\ClockNetCpp.exe`

### 2. Run the Demo

```batch
build\Release\ClockNetCpp.exe
```

You'll see a window with two analog clocks side-by-side:
- **Left**: Black Template (black background with gradient, colored hands)
- **Right**: Fancy Template (white background, elegant design)

### 3. Use in Your Own Project

#### Step 1: Include the necessary files

Copy these folders to your project:
- `ClockControl.h/cpp`
- `Shapes/` folder
- `Templates/` folder
- `Utils/` folder

#### Step 2: Link GDI+ library

Add to your project:
```cpp
#pragma comment(lib, "gdiplus.lib")
```

#### Step 3: Create a clock control

```cpp
#include "ClockControl.h"
#include "Templates/BlackTemplate.h"

// In your WM_CREATE or initialization code:
ClockNet::ClockControl* pClock = new ClockNet::ClockControl();

// Create the control
pClock->Create(
    hwndParent,     // Parent window handle
    10, 10,         // X, Y position
    300, 300,       // Width, Height
    WS_CHILD | WS_VISIBLE
);

// Apply a template
ClockNet::Templates::BlackTemplate template;
pClock->ApplyTemplate(&template);

// That's it! The clock will automatically update.
```

#### Step 4: Cleanup

```cpp
// In your WM_DESTROY:
delete pClock;
```

### 4. Create a Custom Shape

```cpp
#include "Shapes/VectorialShapeBase.h"

class MyCircle : public ClockNet::Shapes::VectorialShapeBase {
protected:
    void OnDraw(ClockNet::Shapes::ClockDrawingContext& context) override {
        // Draw a circle at the center
        float diameter = context.Diameter;
        float size = diameter * 0.1f; // 10% of clock size

        Gdiplus::RectF rect(-size/2, -size/2, size, size);

        if (m_fillColor.GetValue() != 0) {
            context.Graphics->FillEllipse(GetBrush(), rect);
        }

        if (m_outlineColor.GetValue() != 0) {
            context.Graphics->DrawEllipse(GetPen(), rect);
        }
    }

public:
    MyCircle() {
        m_name = L"My Circle";
        m_fillColor = Gdiplus::Color::Blue;
        m_outlineColor = Gdiplus::Color::White;
        m_outlineWidth = 1.0f;
    }
};
```

### 5. Create a Custom Template

```cpp
#include "Templates/TemplateBase.h"
#include "Shapes/Default/FlatBackground.h"
#include "Shapes/Default/DiamondHand.h"
#include "Shapes/Default/Pin.h"

class MyTemplate : public ClockNet::TemplateBase {
protected:
    std::vector<std::shared_ptr<Shapes::IShape>> EnumerateShapes() override {
        std::vector<std::shared_ptr<Shapes::IShape>> shapes;

        // Background
        auto bg = std::make_shared<Shapes::Default::FlatBackground>();
        bg->SetFillColor(Gdiplus::Color(200, 220, 255)); // Light blue
        shapes.push_back(bg);

        // Hour hand
        auto hourHand = std::make_shared<Shapes::Default::DiamondHand>();
        hourHand->SetComponentToDisplay(Shapes::TimeComponent::Hour);
        hourHand->SetFillColor(Gdiplus::Color::DarkBlue);
        hourHand->SetLength(50.0f);
        shapes.push_back(hourHand);

        // Minute hand
        auto minuteHand = std::make_shared<Shapes::Default::DiamondHand>();
        minuteHand->SetComponentToDisplay(Shapes::TimeComponent::Minute);
        minuteHand->SetFillColor(Gdiplus::Color::Blue);
        minuteHand->SetLength(75.0f);
        shapes.push_back(minuteHand);

        // Pin
        auto pin = std::make_shared<Shapes::Default::Pin>();
        pin->SetFillColor(Gdiplus::Color::Red);
        shapes.push_back(pin);

        return shapes;
    }
};

// Use it:
MyTemplate myTemplate;
pClock->ApplyTemplate(&myTemplate);
```

### 6. Add Shapes Manually

```cpp
// Instead of using a template, add shapes manually:
pClock->ClearShapes();

auto bg = std::make_shared<Shapes::Default::FlatBackground>();
bg->SetFillColor(Gdiplus::Color::White);
pClock->AddShape(bg);

auto hand = std::make_shared<Shapes::Default::DiamondHand>();
hand->SetComponentToDisplay(Shapes::TimeComponent::Hour);
hand->SetFillColor(Gdiplus::Color::Blue);
pClock->AddShape(hand);

// etc...
```

### 7. Control the Clock

```cpp
// Stop the timer
pClock->StopTimer();

// Set a specific time
SYSTEMTIME customTime;
GetLocalTime(&customTime);
customTime.wHour = 3;
customTime.wMinute = 15;
customTime.wSecond = 0;
pClock->SetTime(customTime);

// Restart the timer
pClock->StartTimer(100); // Update every 100ms
```

### 8. Customize Appearance

```cpp
// Keep proportions (default: true)
pClock->SetKeepProportions(true);  // Clock stays circular
pClock->SetKeepProportions(false); // Clock can stretch

// Access shapes for customization
auto& shapes = pClock->GetShapes();
for (auto& shape : shapes) {
    if (shape->GetName() == L"Hour Hand") {
        // Modify the hour hand...
    }
}
```

### 9. Multiple Clocks

```cpp
// You can create multiple clock controls:
ClockNet::ClockControl* clock1 = new ClockNet::ClockControl();
ClockNet::ClockControl* clock2 = new ClockNet::ClockControl();
ClockNet::ClockControl* clock3 = new ClockNet::ClockControl();

clock1->Create(hwnd, 10, 10, 200, 200);
clock2->Create(hwnd, 220, 10, 200, 200);
clock3->Create(hwnd, 430, 10, 200, 200);

// Apply different templates
ClockNet::Templates::BlackTemplate black;
ClockNet::Templates::FancyTemplate fancy;

clock1->ApplyTemplate(&black);
clock2->ApplyTemplate(&fancy);
clock3->ApplyTemplate(&black);
```

### 10. Troubleshooting

#### Clock doesn't appear
- Make sure the parent window is visible
- Check the coordinates and size
- Verify GDI+ is linked (`gdiplus.lib`)

#### Clock doesn't update
- Make sure the timer is started: `pClock->StartTimer()`
- Check if the window is receiving WM_TIMER messages

#### Shapes not visible
- Verify shape colors are set (not empty/transparent)
- Check shape visibility: `shape->SetVisible(true)`
- Ensure shapes are added to the clock

#### Build errors
- Make sure you're using Visual Studio 2022 or compatible
- Verify CMake 3.15+ is installed
- Check that Windows SDK is installed

### Performance Tips

1. **Use fewer timer updates**: `StartTimer(1000)` for once per second
2. **Minimize shape count**: Only add necessary shapes
3. **Cache brushes and pens**: Automatically done by base classes
4. **Use release builds**: Much faster than debug

### Example: Complete Minimal Application

```cpp
#include <windows.h>
#include "ClockControl.h"
#include "Templates/FancyTemplate.h"

#pragma comment(lib, "gdiplus.lib")

ClockNet::ClockControl* g_clock = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            g_clock = new ClockNet::ClockControl();
            g_clock->Create(hwnd, 10, 10, 300, 300);
            ClockNet::Templates::FancyTemplate template;
            g_clock->ApplyTemplate(&template);
            break;

        case WM_DESTROY:
            delete g_clock;
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyClock";
    RegisterClass(&wc);

    HWND hwnd = CreateWindow(L"MyClock", L"Clock", WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
                            NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
```

That's it! You now have a fully functional analog clock control in C++.
