# cmake .. -A x64 -T v141 -DQt5_DIR=D:/ProgramFiles/Qt5.12.10/5.12.10/msvc2017_64/lib/cmake/Qt5
cmake_minimum_required(VERSION 3.18)

project(QtPcl)

if (MSVC)
    # 设置 msvc 代码编码格式为 utf-8
    set(CMAKE_C_FLAGS "/source-charset:utf-8 ${CMAKE_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "/source-charset:utf-8 ${CMAKE_CXX_FLAGS}")
    message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()
include_directories("${PROJECT_BINARY_DIR}")
set(Qt5_DIR D:/ProgramFiles/Qt5.12.10/5.12.10/msvc2017_64/lib/cmake/Qt5) 
# init qt
set(CMAKE_AUTOMOC ON) # for meta object compiler
set(CMAKE_AUTORCC ON) # resource files
set(CMAKE_AUTOUIC ON) # UI files

# find package
find_package(Qt5 REQUIRED Widgets)

# PCL
find_package(PCL 1.8.1 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
# find source files, header files and ui files
# aux_source_directory(. DIR_SRCS)
file(GLOB_RECURSE DIR_SRCS    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.cpp ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
file(GLOB_RECURSE DIR_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.h)
file(GLOB_RECURSE DIR_UIS     ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.ui)

# add resource
set(RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.qrc)
qt5_add_resources(RESOURCE_ADDED ${RESOURCE})

add_executable(${PROJECT_NAME}
    ${DIR_SRCS}
    ${DIR_HEADERS}
    ${DIR_UIS}
    ${RESOURCE_ADDED}
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME}
    ${PCL_LIBRARIES}
    Qt5::Widgets
)
