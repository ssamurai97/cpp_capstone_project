
include_directories(imgui)
set(img_src
        imgui/imgui_impl_opengl.cpp
        imgui/imgui_impl_sdl.cpp)
file(GLOB SOURCES  "*.cpp" "*.h" ${img_src})
add_executable(game ${SOURCES} )

target_link_libraries(game PRIVATE
        project_options
        project_warnings
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::glm
        CONAN_PKG::glew
        OpenGL::GL
        SDL2::SDL2
        CONAN_PKG::imgui
        CONAN_PKG::stb
        )
