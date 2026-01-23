cmake_minimum_required(VERSION 3.15)
project(ThendralFrontend)

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../lib/imgui")
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Create the executable
add_executable(thendral_frontend main.cpp ${IMGUI_SOURCES})

target_include_directories(thendral_frontend PRIVATE 
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(thendral_frontend PRIVATE 
    thendral_dll 
    SDL3::SDL3 
    OpenGL::GL
)