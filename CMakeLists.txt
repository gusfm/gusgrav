cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME gusgrav)
project(${PROJECT_NAME} C CXX)

find_package(Threads REQUIRED)

#if(CMAKE_COMPILER_IS_GNUCXX)
#    add_definitions(-Wall -ansi -Wno-deprecated -pthread)
#endif()

#-------------------
# Module source
#-------------------

add_executable(${PROJECT_NAME}
    src/point2d.cc
    src/vector2d.cc
    src/universe.cc
    src/universe_mgr.cc
    src/main.cc)

include_directories(SYSTEM "/usr/include/freetype2")
target_link_libraries(${PROJECT_NAME} m GL glfw ftgl)


#-------------------
# Test
#-------------------
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

add_executable(${PROJECT_TEST_NAME}
    src/point2d.cc
    test/point2d_test.cc)

include_directories(${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_TEST_NAME}
    /usr/lib/libgtest.a
    /usr/lib/libgtest_main.a
    ${CMAKE_THREAD_LIBS_INIT}
    )

add_dependencies(${PROJECT_TEST_NAME} googletest)

add_test(test ${PROJECT_TEST_NAME})
