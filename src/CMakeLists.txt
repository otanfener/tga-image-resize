cmake_minimum_required(VERSION 3.2)
project(halfsize)

add_subdirectory(util)
set(SOURCE_FILES main.cpp)

add_executable(halfsize ${SOURCE_FILES})
target_link_libraries(halfsize util)
install(TARGETS halfsize DESTINATION ${RESIZE_INSTALL_BIN_DIR})