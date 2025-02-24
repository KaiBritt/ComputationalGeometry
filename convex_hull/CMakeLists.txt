cmake_minimum_required(VERSION 3.28)
project(convex_hull)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(/usr/local/include/gtest)


add_executable(convex_hull ConvexHull.cpp main.cpp
        UnitTest.cpp
)
add_executable(UnitTests UnitTest.cpp ConvexHull.cpp)
find_package(GTest CONFIG REQUIRED)
find_package(Matplot++ REQUIRED)
target_link_libraries(convex_hull Matplot++::matplot  GTest::gtest_main)
target_link_libraries(UnitTests  GTest::gtest_main Matplot++::matplot)