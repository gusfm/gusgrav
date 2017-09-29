cmake_minimum_required(VERSION 2.8)
project(gusgrav C CXX)

find_package(Threads REQUIRED)

set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wall -Wextra -std=gnu11 -O3")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O3")

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
    test/list_test.cc)

include_directories(${PROJECT_SOURCE_DIR}/src)
target_link_libraries(gusgrav_test
    gtest
    gtest_main
    ${CMAKE_THREAD_LIBS_INIT}
    )

add_test(test gusgrav_test)
