add_executable(game main.cpp game.cpp)

target_link_libraries(game PRIVATE project_options project_warnings CONAN_PKG::docopt.cpp
CONAN_PKG::fmt CONAN_PKG::spdlog SDL2::SDL2)
