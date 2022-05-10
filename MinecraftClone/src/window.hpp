#pragma once

#include "pch.hpp"

namespace mcc
{
class WindowImpl;

class Window
{
  public:
    Window();
    Window(unsigned int width, unsigned int height, std::string_view title);

    ~Window();

    void create(unsigned int width, unsigned int height, std::string_view title);
    void close();
    bool shouldClose();
    void pollEvents();

  private:
    std::unique_ptr<WindowImpl> m_impl;
};
}  // namespace mcc
