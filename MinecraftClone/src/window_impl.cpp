#include "window_impl.hpp"

#ifdef _WIN32
#include "window_impl_win32.hpp"
using WindowImplType = mcc::WindowImplWin32;
#endif

namespace mcc
{
std::unique_ptr<WindowImpl> WindowImpl::create(
    unsigned int width, unsigned int height, std::string_view title)
{
    return std::make_unique<WindowImplType>(width, height, title);
}
}  // namespace mcc