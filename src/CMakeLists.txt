find_package(Characters REQUIRED)
find_package(Allocators REQUIRED)

set(krall_SOURCES main.c game.c character_sheet.c party.c rng.c comparison.c)
set(krall_PRIVATE_INCLUDE_DIRECTORIES $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/include> ${CHARACTERS_INCLUDE_DIR} ${ALLOCATORS_INCLUDE_DIR})
set(krall_LINK_LIBRARIES m mimalloc ${CHARACTERS_LIBRARIES})

if (${Renderer} STREQUAL "TUI")
   add_compile_definitions(TUI)
   list(APPEND krall_SOURCES gui/notcurses/tui.c)
   list(APPEND krall_PRIVATE_INCLUDE_DIRECTORIES $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/gui/notcurses/include>)
   list(APPEND krall_LINK_LIBRARIES notcurses notcurses-core)
endif()

add_executable(krall ${krall_SOURCES})

target_include_directories(krall PRIVATE ${krall_PRIVATE_INCLUDE_DIRECTORIES})
target_link_libraries(krall ${krall_LINK_LIBRARIES})
