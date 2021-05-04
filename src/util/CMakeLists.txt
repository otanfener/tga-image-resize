cmake_minimum_required(VERSION 3.2)
project(util C CXX)

set(SOURCE_FILES
        tga.cpp
        decoder.cpp
        encoder.cpp
        image_processor.cpp
        exception.cpp)

add_library(util STATIC ${SOURCE_FILES})

install(TARGETS util DESTINATION ${RESIZE_INSTALL_LIB_DIR})
install(FILES tga.hpp decoder.hpp encoder.hpp image_processor.hpp exception.hpp DESTINATION ${RESIZE_INSTALL_INCLUDE_DIR})
