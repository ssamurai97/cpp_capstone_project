cmake_minimum_required(VERSION 3.13)

# Set the project name to your project name,
project(my_game CXX)
include(cmake/StandardProjectSettings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if (ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(project_options INTERFACE -ftime-trace)
    endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)


# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
#set_project_warnings(project_warnings)

include(cmake/PVS-Studio.cmake)
include(cmake/Conan.cmake)
run_conan()
include(FindPkgConfig)

find_package(OpenGL REQUIRED)

add_subdirectory(src)

pvs_studio_add_target(TARGET ${PROJECT_NAME}.analyze ALL
        ANALYZE game
        OUTPUT FORMAT errorfile
        PREPROCESSOR clang
        LOG target_${PROJECT_NAME}.err
        )