cmake_minimum_required(VERSION 3.2)
project(halfsize_tests)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES src/main.cpp src/halfsize_tests.cpp)

add_executable(halfsize_tests ${SOURCE_FILES})
target_link_libraries(halfsize_tests gtest)
install(TARGETS halfsize_tests DESTINATION bin)