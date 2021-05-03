cmake_minimum_required(VERSION 3.2)
project(halfsize)

set(SOURCE_FILES
        main.cpp
        main.hpp
        decoder.cpp
        decoder.hpp
        encoder.cpp
        encoder.hpp
        exception.hpp
        exception.cpp
        image_processor.cpp
        image_processor.hpp
        tga.cpp
        tga.hpp
        )

add_executable(halfsize ${SOURCE_FILES})
install(TARGETS halfsize DESTINATION ${RESIZE_INSTALL_BIN_DIR})