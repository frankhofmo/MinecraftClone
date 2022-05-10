#pragma once

#include "pch.hpp"

namespace mcc
{
class WindowImpl
{
  public:
    virtual ~WindowImpl() = default;

    static std::unique_ptr<WindowImpl> create(
        unsigned int width, unsigned int height, std::string_view title);

    virtual bool shouldClose() = 0;
    virtual void pollEvents() = 0;
};
}  // namespace mcc