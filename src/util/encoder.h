//
// Created by ozan on 2021-05-03.
//

#ifndef UBISOFT_ASSIGMENT_ENCODER_H
#define UBISOFT_ASSIGMENT_ENCODER_H

#include "tga.h"
#include <fstream>
class Encoder {
public:
    Encoder(std::ofstream& stream, Tga& image): m_Image(image), m_Stream(stream){};

private:
    std::ofstream&  m_Stream;
    Tga& m_Image;
public:
    bool createImageHeader(uint16_t width, uint16_t height, uint8_t bits);
    bool writeImageToFile(std::vector<uint8_t>& b);
};


#endif //UBISOFT_ASSIGMENT_ENCODER_H
