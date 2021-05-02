//
// Created by ozan on 2021-05-01.
//

#include "tga.h"
uint32_t Tga::Move(uint32_t index, uint8_t direction) {
    uint32_t new_position{0};
    switch (direction) {
        case 'R':
            new_position = index + m_pixelSize;
            break;
        case 'U':
            new_position = index - m_Header.Width*m_pixelSize;
            break;
        case 'D':
            new_position = index + m_Header.Width*m_pixelSize;
            break;
        case 'X':
            new_position = index + (m_Header.Width+1)*m_pixelSize;
            break;
        default:
            new_position = index - m_pixelSize;
            break;
    }

    return new_position;
}


