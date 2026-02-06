// ClockNet C++ Port
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include "ClockControl.h"
#include "Templates/TemplateBase.h"
#include "Shapes/ClockDrawingContext.h"
#include <windowsx.h>

namespace ClockNet {

    const wchar_t* ClockControl::s_className = L"ClockNetControl";
    ATOM ClockControl::s_classAtom = 0;
    bool ClockControl::s_classRegistered = false;

    ClockControl::ClockControl()
        : m_hwnd(nullptr)
        , m_gdiplusToken(0)
        , m_keepProportions(true)
        , m_diameter(200.0f)
        , m_radius(0)
        , m_centerX(0)
        , m_centerY(0)
        , m_scaleX(1.0f)
        , m_scaleY(1.0f)
        , m_timerId(0) {

        // Initialize GDI+
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, nullptr);

        // Initialize time to current time
        GetLocalTime(&m_time);
    }

    ClockControl::~ClockControl() {
        StopTimer();

        if (m_hwnd) {
            DestroyWindow(m_hwnd);
        }

        // Cleanup shapes
        m_shapes.clear();

        // Shutdown GDI+
        if (m_gdiplusToken) {
            Gdiplus::GdiplusShutdown(m_gdiplusToken);
        }
    }

    bool ClockControl::RegisterWindowClass(HINSTANCE hInstance) {
        if (s_classRegistered)
            return true;

        WNDCLASSEXW wc = { 0 };
        wc.cbSize = sizeof(WNDCLASSEXW);
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wc.lpfnWndProc = StaticWndProc;
        wc.cbWndExtra = sizeof(ClockControl*);
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszClassName = s_className;

        s_classAtom = RegisterClassExW(&wc);
        if (s_classAtom == 0) {
            return false;
        }

        s_classRegistered = true;
        return true;
    }

    bool ClockControl::Create(HWND parent, int x, int y, int width, int height, DWORD style) {
        HINSTANCE hInstance = GetModuleHandle(nullptr);

        if (!s_classRegistered) {
            if (!RegisterWindowClass(hInstance)) {
                return false;
            }
        }

        m_hwnd = CreateWindowExW(
            0,
            MAKEINTATOM(s_classAtom),
            L"",
            style,
            x, y, width, height,
            parent,
            NULL,
            hInstance,
            this
        );

        if (!m_hwnd)
        {
            LPVOID lpMsgBuf;
            DWORD dw = GetLastError();

            if (FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                dw,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&lpMsgBuf,
                0, NULL) == 0) {
                MessageBox(NULL, TEXT("FormatMessage failed"), TEXT("Error"), MB_OK);
                ExitProcess(dw);
            }

            MessageBox(NULL, (LPCTSTR)lpMsgBuf, TEXT("Error"), MB_OK);

            LocalFree(lpMsgBuf);

            return false;
        }

        // Store this pointer in window data
        SetWindowLongPtrW(m_hwnd, 0, reinterpret_cast<LONG_PTR>(this));

        CalculateDimensions();
        StartTimer();

        return true;
    }

    LRESULT CALLBACK ClockControl::StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        ClockControl* pThis = nullptr;

        if (msg == WM_NCCREATE) {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            pThis = reinterpret_cast<ClockControl*>(pCreate->lpCreateParams);
            SetWindowLongPtrW(hwnd, 0, reinterpret_cast<LONG_PTR>(pThis));
        } else {
            pThis = reinterpret_cast<ClockControl*>(GetWindowLongPtrW(hwnd, 0));
        }

        if (pThis) {
            return pThis->WndProc(hwnd, msg, wParam, lParam);
        }

        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    LRESULT ClockControl::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch (msg) {
            case WM_PAINT:
                OnPaint();
                return 0;

            case WM_SIZE:
                OnSize();
                return 0;

            case WM_TIMER:
                OnTimer();
                return 0;

            case WM_ERASEBKGND:
                return 1; // Prevent flicker

            default:
                return DefWindowProcW(hwnd, msg, wParam, lParam);
        }
    }

    void ClockControl::OnPaint() {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);

        // Create memory DC for double buffering
        RECT rect;
        GetClientRect(m_hwnd, &rect);
        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP memBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);

        // Create Graphics object
        Gdiplus::Graphics graphics(memDC);
        graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
        graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
        graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);

        // Clear background
        Gdiplus::SolidBrush bgBrush(Gdiplus::Color(255, 240, 240, 240));
        graphics.FillRectangle(&bgBrush, 0, 0, rect.right, rect.bottom);

        if (m_radius > 0) {
            // Save original transform
            Gdiplus::Matrix originalMatrix;
            graphics.GetTransform(&originalMatrix);

            // Apply transformations
            graphics.TranslateTransform(m_centerX, m_centerY);
            graphics.ScaleTransform(m_scaleX, m_scaleY);

            // Get center matrix
            Gdiplus::Matrix centerMatrix;
            graphics.GetTransform(&centerMatrix);

            // Draw shapes
            DrawShapes(&graphics, centerMatrix);
        }

        // Copy to screen
        BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);

        // Cleanup
        SelectObject(memDC, oldBitmap);
        DeleteObject(memBitmap);
        DeleteDC(memDC);

        EndPaint(m_hwnd, &ps);
    }

    void ClockControl::OnSize() {
        CalculateDimensions();
        InvalidateRect(m_hwnd, nullptr, FALSE);
    }

    void ClockControl::OnTimer() {
        GetLocalTime(&m_time);
        InvalidateRect(m_hwnd, nullptr, FALSE);
    }

    void ClockControl::CalculateDimensions() {
        RECT rect;
        GetClientRect(m_hwnd, &rect);

        float drawableWidth = (float)(rect.right - rect.left);
        float drawableHeight = (float)(rect.bottom - rect.top);

        if (drawableWidth < 0 || drawableHeight < 0) {
            m_radius = 0;
            return;
        }

        if (m_keepProportions) {
            if (drawableWidth < drawableHeight) {
                m_scaleX = drawableWidth / m_diameter;
                m_scaleY = drawableWidth / m_diameter;
            } else {
                m_scaleX = drawableHeight / m_diameter;
                m_scaleY = drawableHeight / m_diameter;
            }
        } else {
            m_scaleX = drawableWidth / m_diameter;
            m_scaleY = drawableHeight / m_diameter;
        }

        m_radius = m_diameter / 2.0f;
        m_centerX = drawableWidth / 2.0f;
        m_centerY = drawableHeight / 2.0f;
    }

    void ClockControl::DrawShapes(Gdiplus::Graphics* graphics, const Gdiplus::Matrix& initialMatrix) {
        Shapes::ClockDrawingContext context(graphics, m_time, m_diameter);

        for (auto& shape : m_shapes) {
            if (!shape)
                continue;

            graphics->SetTransform(&initialMatrix);
            shape->Draw(context);
        }
    }

    void ClockControl::SetKeepProportions(bool keep) {
        m_keepProportions = keep;
        CalculateDimensions();
        InvalidateRect(m_hwnd, nullptr, FALSE);
    }

    void ClockControl::SetTime(const SYSTEMTIME& time) {
        m_time = time;
        InvalidateRect(m_hwnd, nullptr, FALSE);
    }

    void ClockControl::AddShape(std::shared_ptr<Shapes::IShape> shape) {
        m_shapes.push_back(shape);
        InvalidateRect(m_hwnd, nullptr, FALSE);
    }

    void ClockControl::ClearShapes() {
        m_shapes.clear();
        InvalidateRect(m_hwnd, nullptr, FALSE);
    }

    void ClockControl::ApplyTemplate(TemplateBase* clockTemplate) {
        if (!clockTemplate)
            return;

        ClearShapes();
        auto shapes = clockTemplate->GetShapes();
        for (auto& shape : shapes) {
            AddShape(shape);
        }
    }

    void ClockControl::StartTimer(UINT intervalMs) {
        if (m_timerId) {
            StopTimer();
        }
        m_timerId = SetTimer(m_hwnd, 1, intervalMs, nullptr);
    }

    void ClockControl::StopTimer() {
        if (m_timerId) {
            KillTimer(m_hwnd, m_timerId);
            m_timerId = 0;
        }
    }

} // namespace ClockNet
