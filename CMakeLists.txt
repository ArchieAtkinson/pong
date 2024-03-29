cmake_minimum_required(VERSION 3.21)

set (CMAKE_CXX_STANDARD 20)

# Config
project(pong VERSION 1.0.0 LANGUAGES C CXX ASM)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

find_library(PANEL_LIB NAMES panel libpanel REQUIRED)
find_library(FMT_LIB NAMES fmt fmtlib libfmt REQUIRED)

# Source
set(SOURCES 
src/main.cpp
src/debug_win.cpp
src/debug_win.hpp
src/KeyHold.cpp
src/KeyHold.hpp
src/util.hpp
src/Paddle.hpp
src/Paddle.cpp
)

add_executable(pong ${SOURCES})

target_include_directories(
    pong
    PRIVATE ${CMAKE_SOURCE_DIR}/src 
    PRIVATE ${CURSES_INCLUDE_DIRSCURSES_INCLUDE_DIRS}
)

target_link_libraries(
    pong
    ${CURSES_LIBRARIES}
    ${PANEL_LIB}
    ${FMT_LIB}
) 

target_compile_definitions(
pong 
PRIVATE _LIBCPP_HAS_NO_INCOMPLETE_FORMAT
PRIVATE _XOPEN_SOURCE_EXTENDED # Required for Unicode
)