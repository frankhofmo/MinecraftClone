#include <iostream>
#include "window.hpp"

int main()
{
    mcc::Window window(1280, 960, "First window");

    while (!window.shouldClose())
    {
        window.pollEvents();
    }

    return 0;
}
