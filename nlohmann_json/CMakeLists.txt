# CMakeLists.txt
cmake_minimum_required(VERSION 3.1)

project(demo VERSION 3.11.2 LANGUAGES CXX)
add_executable(demo main.cpp)
target_include_directories(demo  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/single_include)
