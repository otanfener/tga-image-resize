//
// Created by ozan on 2021-05-01.
//

#ifndef UBISOFT_ASSIGMENT_TGA_H
#define UBISOFT_ASSIGMENT_TGA_H

#include <cstdint>
#include <vector>

typedef struct __attribute__((__packed__))  {
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
}TgaHeader_t;

typedef enum{
    NO_IMAGE=0,
    UNCOMPRESSED_COLORMAP_IMAGE=1,
    UNCOMPRESSED_TRUECOLOR_IMAGE=2,
    UNCOMPRESSED_GRAYSCALE_IMAGE=3,
    RLE_COLORMAP_IMAGE=9,
    RLE_TRUECOLOR_IMAGE=10,
    RLE_GRAYSCALE_IMAGE=11
}TgaImageType_t;


class Tga {
public:
    
    TgaHeader_t tgaHeader;
    std::vector <uint8_t> imageBuffer;
    uint32_t pixelSize;

public:
    uint32_t Seek(uint32_t index, uint8_t direction);

};


#endif //UBISOFT_ASSIGMENT_TGA_H
