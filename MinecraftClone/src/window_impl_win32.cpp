#include "window_impl_win32.hpp"
#include "pch.hpp"

namespace
{
constexpr auto wndClassName = "MCC_Window";
}

namespace mcc
{
WindowImplWin32::WindowImplWin32(unsigned int width, unsigned int height, std::string_view title)
    : m_handle(nullptr)
    , m_shouldClose(false)
{
    registerWindowClass();

    m_handle = CreateWindow(wndClassName,
        "Hello world!",
        WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        this);
}

WindowImplWin32::~WindowImplWin32()
{
    if (m_handle)
    {
        DestroyWindow(m_handle);
    }

    UnregisterClass(wndClassName, GetModuleHandleW(nullptr));
}

bool WindowImplWin32::shouldClose()
{
    return m_shouldClose;
}

void WindowImplWin32::pollEvents()
{
    MSG message{};
    while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

void WindowImplWin32::processEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
    if (m_handle == nullptr)
    {
        return;
    }

    switch (message)
    {
    case WM_CLOSE:
        m_shouldClose = true;
        break;
    }
}

void WindowImplWin32::registerWindowClass()
{
    WNDCLASS windowClass{};
    windowClass.lpfnWndProc = &WindowImplWin32::windowProc;
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.hInstance = GetModuleHandleW(nullptr);
    windowClass.lpszClassName = wndClassName;

    RegisterClass(&windowClass);
}

LRESULT WindowImplWin32::windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_CREATE)
    {
        auto window =
            reinterpret_cast<LONG_PTR>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
        SetWindowLongPtr(handle, GWLP_USERDATA, window);
    }

    WindowImplWin32* window =
        handle ? reinterpret_cast<WindowImplWin32*>(GetWindowLongPtr(handle, GWLP_USERDATA))
               : nullptr;

    if (window)
    {
        window->processEvent(message, wParam, lParam);
    }

    if (message == WM_CLOSE)
    {
        return 0;
    }

    if ((message == WM_SYSCOMMAND) && (wParam == SC_KEYMENU))
    {
        return 0;
    }

    return DefWindowProc(handle, message, wParam, lParam);
}

}  // namespace mcc