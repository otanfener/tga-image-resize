//
// Created by ozan on 2021-05-01.
//

#ifndef UBISOFT_ASSIGMENT_TGA_H
#define UBISOFT_ASSIGMENT_TGA_H

#include <cstdint>
#include <vector>
#include <memory>

typedef struct __attribute__((__packed__))  {
    uint8_t IDLength;
    uint8_t ColorMapType;
    uint8_t ImageType;

    uint16_t ColorMapOrigin;
    uint16_t ColorMapLength;
    uint8_t ColorMapEntrySize;

    uint16_t XOrigin;
    uint16_t YOrigin;
    uint16_t Width;
    uint16_t Height;
    uint8_t Bits;
    uint8_t ImageDescriptor;
}TgaHeader_t;

class Tga {
public:
    
    TgaHeader_t header;
    std::vector <uint8_t> buffer;
    uint32_t pixelSize;

public:
    uint32_t Seek(uint32_t index, uint8_t direction);

};


#endif //UBISOFT_ASSIGMENT_TGA_H
