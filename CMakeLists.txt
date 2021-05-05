cmake_minimum_required(VERSION 3.2)
project(ubisoft_assignment)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    add_compile_options("/W3" "/std:c++17" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-std=c++17" "-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options("-stdlib=libc++")
    else()
    endif()
endif()

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(RESIZE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(RESIZE_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(RESIZE_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)


include_directories(${RESIZE_INSTALL_INCLUDE_DIR})

add_subdirectory(src)
