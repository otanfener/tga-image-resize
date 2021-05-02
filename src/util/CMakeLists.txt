cmake_minimum_required(VERSION 3.2)
project(util C CXX)

set(SOURCE_FILES
        tga.cpp
        decoder.cpp
        encoder.cpp
        image_processor.cpp
        )

add_library(util STATIC ${SOURCE_FILES})

install(TARGETS util DESTINATION ${RESIZE_INSTALL_LIB_DIR})
install(FILES tga.h decoder.h encoder.h image_processor.h DESTINATION ${RESIZE_INSTALL_INCLUDE_DIR})
