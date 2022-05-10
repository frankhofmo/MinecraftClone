cmake_minimum_required(VERSION 3.22)

find_package(Vulkan REQUIRED)

add_executable(MinecraftClone "src/main.cpp" "src/window.hpp" "src/window.cpp" "src/pch.hpp" "src/window_impl.hpp" "src/window_impl.cpp" "src/window_impl_win32.hpp" "src/window_impl_win32.cpp")
target_compile_features(MinecraftClone PRIVATE cxx_std_20)
target_precompile_headers(MinecraftClone PRIVATE "src/pch.hpp")
target_include_directories(MinecraftClone PRIVATE "${Vulkan_INCLUDE_DIR}")
target_link_libraries(MinecraftClone PRIVATE "${Vulkan_LIBRARY}")
