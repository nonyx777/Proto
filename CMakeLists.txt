cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(proto VERSION 1.0)

find_package(SFML 2 REQUIRED network audio graphics window system)

#include catch2 for the tests
add_subdirectory(tests)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(proto ${SRC_FILES})

target_include_directories(proto PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${SFML_INCLUDE_DIR})
target_link_libraries(proto PUBLIC -lsfml-window -lsfml-graphics -lsfml-system)
