cmake_minimum_required(VERSION 3.2)
project(ubisoft_assigment)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(RESIZE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(RESIZE_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(RESIZE_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)


include_directories(${RESIZE_INSTALL_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)
