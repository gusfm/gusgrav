cmake_minimum_required(VERSION 2.8)
project(gusgrav C)

set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wall -Wextra -std=gnu11 -O3")

# Gusgrav
add_executable(gusgrav
    src/list.c
    src/vector.c
    src/body.c
    src/universe.c
    src/window.c
    src/main.c
    )
target_link_libraries(gusgrav m GL glfw)

# Test
enable_testing()

add_executable(gusgrav_test
    src/list.c
    test/list_test.c
    test/main.c)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_test(test gusgrav_test)
