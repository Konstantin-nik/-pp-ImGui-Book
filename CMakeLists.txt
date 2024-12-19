cmake_minimum_required(VERSION 3.14)
project(DearImGuiDemoProject)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(libs/SDL2)

file(GLOB IMGUI_SOURCES
    libs/imgui/imgui.cpp
    libs/imgui/imgui_draw.cpp
    libs/imgui/imgui_widgets.cpp
    libs/imgui/backends/imgui_impl_sdl2.cpp
    libs/imgui/backends/imgui_impl_sdlrenderer2.cpp
)

file(GLOB SOURCES
    src/*.cpp
    src/**/*.cpp
)

add_executable(DearImGuiDemoProject ${SOURCES} ${IMGUI_SOURCES})

target_include_directories(DearImGuiDemoProject PRIVATE
    libs/imgui
    libs/SDL2/include
)

target_link_libraries(DearImGuiDemoProject
    SDL2-static
)