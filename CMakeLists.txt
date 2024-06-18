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

set(HEADERS
    # include/api/controllers/cameraController.h
    # include/api/models/camera.h
)

set(SOURCES
    # src/api/controllers/cameraController.cpp
    # src/api/models/camera.cpp
    src/main.cpp
)

# target_include_directories(${PROJECT_NAME} PRIVATE include)
# target_link_libraries(${PROJECT_NAME} PRIVATE
#     Qt6::Core
#     Qt6::Gui
#     Qt6::Multimedia
#     Qt6::Qml
#     Qt6::Quick
#     Qt6::QuickControls2
# )

add_executable(${PROJECT_NAME} ${SOURCES})

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
