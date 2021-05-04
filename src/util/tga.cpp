//
// Created by ozan on 2021-05-01.
//

#include "tga.hpp"

uint32_t Tga::Seek(uint32_t index, uint8_t direction) {
    uint32_t new_position{0};
    switch (direction) {
        case 'R':
            new_position = index + pixelSize;
            break;
        case 'U':
            new_position = index - this->tgaHeader.width * pixelSize;
            break;
        case 'D':
            new_position = index + this->tgaHeader.width * pixelSize;
            break;
        case 'X':
            new_position = index + (this->tgaHeader.width + 1) * pixelSize;
            break;
        default:
            new_position = index - pixelSize;
            break;
    }

    return new_position;
}


