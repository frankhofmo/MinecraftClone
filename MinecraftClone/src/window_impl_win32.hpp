#pragma once

#include "window_impl.hpp"

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

namespace mcc
{
class WindowImplWin32 : public WindowImpl
{
  public:
    WindowImplWin32(unsigned int width, unsigned int height, std::string_view title);
    ~WindowImplWin32() override;

    bool shouldClose() override;
    void pollEvents() override;

  private:
    void processEvent(UINT message, WPARAM wParam, LPARAM lParam);
    static void registerWindowClass();
    static LRESULT CALLBACK windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

    HWND m_handle;
    bool m_shouldClose;
};
}  // namespace mcc
