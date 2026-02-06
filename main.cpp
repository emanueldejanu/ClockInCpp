// ClockNet C++ Port - Demo Application
// Copyright (C) 2025
// Original: Copyright (C) 2010 Dust in the Wind
// GPL v3 License

#include <windows.h>
#include <commctrl.h>
#include "ClockControl.h"
#include "Templates/BlackTemplate.h"
#include "Templates/FancyTemplate.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "gdiplus.lib")

// Global variables
HINSTANCE g_hInstance = nullptr;
HWND g_hMainWindow = nullptr;
ClockNet::ClockControl* g_pClockControl1 = nullptr;
ClockNet::ClockControl* g_pClockControl2 = nullptr;

// Forward declarations
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void CreateControls(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    g_hInstance = hInstance;

    // Initialize common controls
    INITCOMMONCONTROLSEX icc;
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icc);

    // Register window class
    WNDCLASSEXW wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"ClockNetDemoApp";
    wc.lpszMenuName = nullptr;

    if (!RegisterClassExW(&wc)) {
        MessageBoxW(nullptr, L"Window Registration Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Create main window
    g_hMainWindow = CreateWindowExW(
        0,
        L"ClockNetDemoApp",
        L"ClockNet C++ Demo - Analog Clock Control",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        900, 500,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!g_hMainWindow) {
        MessageBoxW(nullptr, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(g_hMainWindow, nCmdShow);
    UpdateWindow(g_hMainWindow);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            CreateControls(hwnd);
            break;

        case WM_SIZE:
            {
                int width = LOWORD(lParam);
                int height = HIWORD(lParam);

                // Resize clock controls
                if (g_pClockControl1) {
                    SetWindowPos(g_pClockControl1->GetHwnd(), nullptr,
                                10, 50, width / 2 - 20, height - 60,
                                SWP_NOZORDER);
                }

                if (g_pClockControl2) {
                    SetWindowPos(g_pClockControl2->GetHwnd(), nullptr,
                                width / 2 + 10, 50, width / 2 - 20, height - 60,
                                SWP_NOZORDER);
                }
            }
            break;

        case WM_DESTROY:
            // Cleanup
            delete g_pClockControl1;
            delete g_pClockControl2;
            g_pClockControl1 = nullptr;
            g_pClockControl2 = nullptr;

            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    return 0;
}

void CreateControls(HWND hwnd) {
    if (!IsWindow(hwnd)) {
        MessageBoxW(hwnd, L"Parent window is not a window!", L"Error", MB_OK | MB_ICONERROR);
    }

    // Create title label
    CreateWindowW(
        L"STATIC",
        L"ClockNet C++ Demo - Two Clock Templates",
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        10, 10, 880, 30,
        hwnd,
        nullptr,
        g_hInstance,
        nullptr
    );

    // Create first clock control with Black Template
    g_pClockControl1 = new ClockNet::ClockControl();
    if (!g_pClockControl1->Create(hwnd, 10, 50, 400, 400)) {
        MessageBoxW(hwnd, L"Failed to create first clock control!", L"Error", MB_OK | MB_ICONERROR);
        delete g_pClockControl1;
        g_pClockControl1 = nullptr;
        return;
    }

    // Apply Black Template
    ClockNet::Templates::BlackTemplate blackTemplate;
    g_pClockControl1->ApplyTemplate(&blackTemplate);

    // Label for first clock
    CreateWindowW(
        L"STATIC",
        L"Black Template",
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        10, 20, 400, 20,
        hwnd,
        nullptr,
        g_hInstance,
        nullptr
    );

    // Create second clock control with Fancy Template
    g_pClockControl2 = new ClockNet::ClockControl();
    if (!g_pClockControl2->Create(hwnd, 430, 50, 400, 400)) {
        MessageBoxW(hwnd, L"Failed to create second clock control!", L"Error", MB_OK | MB_ICONERROR);
        delete g_pClockControl2;
        g_pClockControl2 = nullptr;
        return;
    }

    // Apply Fancy Template
    ClockNet::Templates::FancyTemplate fancyTemplate;
    g_pClockControl2->ApplyTemplate(&fancyTemplate);

    // Label for second clock
    CreateWindowW(
        L"STATIC",
        L"Fancy Template",
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        430, 20, 400, 20,
        hwnd,
        nullptr,
        g_hInstance,
        nullptr
    );
}
