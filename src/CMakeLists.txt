

file(GLOB SOURCES "*.cpp")
add_executable(game ${SOURCES} )

target_link_libraries(game PRIVATE project_options project_warnings CONAN_PKG::docopt.cpp
CONAN_PKG::fmt CONAN_PKG::spdlog SDL2::SDL2 ${SDL2IMAGE_LIBRARIES})
