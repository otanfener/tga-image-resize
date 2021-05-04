//
// Created by ozan on 2021-05-01.
//

#ifndef UBISOFT_ASSIGMENT_TGA_HPP
#define UBISOFT_ASSIGMENT_TGA_HPP

#include <cstdint>
#include <vector>

typedef struct __attribute__((__packed__)) {
    uint8_t idLength;
    uint8_t colorMapType;
    uint8_t imageType;

    uint16_t colorMapOrigin;
    uint16_t colorMapLength;
    uint8_t colorMapEntrySize;

    uint16_t xOrigin;
    uint16_t yOrigin;
    uint16_t width;
    uint16_t height;
    uint8_t bits;
    uint8_t imageDescriptor;
} TgaHeader_t;

typedef enum {
    UNCOMPRESSED_TRUECOLOR_IMAGE = 2,
    UNCOMPRESSED_GRAYSCALE_IMAGE = 3,
    RLE_TRUECOLOR_IMAGE = 10,
    IMAGE_LAST
} TgaImageType_t;

typedef enum {
    RLE_CHUNK_BITMASK = 0x80,
    RLE_LENGTH_BITMASK = 0x7F,
    BITMASK_LAST
} tgaBitmask_t;

class Tga {
public:

    TgaHeader_t tgaHeader;
    std::vector<uint8_t> imageBuffer;
    uint32_t pixelSize;

public:
    uint32_t Seek(uint32_t index, uint8_t direction);

};


#endif //UBISOFT_ASSIGMENT_TGA_HPP