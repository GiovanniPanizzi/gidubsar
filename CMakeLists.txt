cmake_minimum_required(VERSION 3.15)
project(gidubsar VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)

add_executable(gidubsar main.cpp)

target_include_directories(gidubsar PRIVATE ${CURSES_INCLUDE_DIR})

target_link_libraries(gidubsar PRIVATE ${CURSES_LIBRARIES})