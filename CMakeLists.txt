cmake_minimum_required(VERSION 3.19)

project(construction CXX)

# Explicitly opt in to modern CMake behaviors to avoid warnings with recent
# versions of CMake.
if(POLICY CMP0063)
    cmake_policy(SET CMP0063 NEW)
endif()

# Use ccache for faster rebuilds
find_program(CCACHE_PRG ccache)
if(CCACHE_PRG)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CMAKE_COMMAND} -E env
        CCACHE_SLOPPINESS=pch_defines,time_macros ${CCACHE_PRG})
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

set(HEADERS
    include/constants.h
    include/world.h
)

set(SOURCES
    src/main.cpp
    src/world.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Compiler options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -W3)

    # Disable warnings that give too many false positives.
    target_compile_options(${PROJECT_NAME} PRIVATE -wd4311 -wd4146 -wd4003 -wd4715)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic
        -Wno-unused-parameter
        -Wstrict-prototypes -Wshadow -Wconversion -Wvla
        -Wdouble-promotion
        -Wmissing-noreturn
        -Wmissing-format-attribute
        -Wmissing-prototypes
        -fsigned-char)
endif()
