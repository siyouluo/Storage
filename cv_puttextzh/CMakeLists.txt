# cmake needs this line
cmake_minimum_required(VERSION 3.18)

# Define project name
project(OpenCVputTextZH)

if (MSVC)
    # 设置 msvc 代码编码格式为 utf-8
    set(CMAKE_C_FLAGS "/source-charset:utf-8 ${CMAKE_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "/source-charset:utf-8 ${CMAKE_CXX_FLAGS}")
    message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()

find_package(OpenCV 3 REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

# Declare the executable target built from your sources
add_executable(demo main.cpp)

# Link your application with OpenCV libraries
target_link_libraries(demo PRIVATE ${OpenCV_LIBS})
