#include "window.hpp"
#include "window_impl.hpp"

namespace mcc
{
Window::Window()
    : m_impl()
{
}

Window::Window(unsigned int width, unsigned int height, std::string_view title)
    : m_impl()
{
    create(width, height, title);
}

Window::~Window()
{
    close();
}

void Window::create(unsigned int width, unsigned int height, std::string_view title)
{
    close();

    m_impl = WindowImpl::create(width, height, title);
}

void Window::close()
{
    m_impl.reset();
}

bool Window::shouldClose()
{
    return m_impl->shouldClose();
}

void Window::pollEvents()
{
    if (!m_impl)
        return;

    m_impl->pollEvents();
}
}  // namespace mcc