cmake_minimum_required(VERSION 3.18)

project(Krall)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_compile_options(-pedantic -Wall -Wextra -Werror -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition)

add_subdirectory(src)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(Renderer "TUI" CACHE STRING "Chosen at CMake configure time")
set(RendererValues "TUI;Qt GUI" CACHE STRING "Available rendering options")
set_property(CACHE Renderer PROPERTY STRINGS ${RendererValues})

message(STATUS "Renderer='${Renderer}'")
