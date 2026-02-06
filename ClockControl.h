// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include <memory>
#include "Shapes/IShape.h"

namespace ClockNet {

    // Forward declarations
    class TemplateBase;

    /// <summary>
    /// A Windows control that displays an analog clock
    /// </summary>
    class ClockControl {
    private:
        HWND m_hwnd;
        ULONG_PTR m_gdiplusToken;
        std::vector<std::shared_ptr<Shapes::IShape>> m_shapes;

        SYSTEMTIME m_time;
        bool m_keepProportions;
        float m_diameter;
        float m_radius;
        float m_centerX;
        float m_centerY;
        float m_scaleX;
        float m_scaleY;

        // Timer for updating the clock
        UINT_PTR m_timerId;

    static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

        void OnPaint();
        void OnSize();
        void OnTimer();
        void CalculateDimensions();
        void DrawShapes(Gdiplus::Graphics* graphics, const Gdiplus::Matrix& initialMatrix);

        static const wchar_t* s_className;
        static bool s_classRegistered;
        static ATOM s_classAtom;

    public:
        ClockControl();
        ~ClockControl();

        // Window management
        bool Create(HWND parent, int x, int y, int width, int height, DWORD style = WS_CHILD | WS_VISIBLE);
        HWND GetHwnd() const { return m_hwnd; }

        // Properties
        bool GetKeepProportions() const { return m_keepProportions; }
        void SetKeepProportions(bool keep);

        SYSTEMTIME GetTime() const { return m_time; }
        void SetTime(const SYSTEMTIME& time);

        // Shape management
        std::vector<std::shared_ptr<Shapes::IShape>>& GetShapes() { return m_shapes; }
        void AddShape(std::shared_ptr<Shapes::IShape> shape);
        void ClearShapes();

        // Template management
        void ApplyTemplate(TemplateBase* clockTemplate);

        // Timer control
        void StartTimer(UINT intervalMs = 100);
        void StopTimer();

        // Static registration
        static bool RegisterWindowClass(HINSTANCE hInstance);
    };

} // namespace ClockNet
