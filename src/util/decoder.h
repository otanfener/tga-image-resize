//
// Created by ozan on 2021-05-01.
//

#ifndef UBISOFT_ASSIGMENT_DECODER_H
#define UBISOFT_ASSIGMENT_DECODER_H

#include <fstream>
#include "tga.h"
#include <vector>

class Decoder {
public:
    Decoder(std::ifstream &stream, Tga &image) : m_Image(image), m_Stream(stream) {};

private:
    std::ifstream &m_Stream;
    Tga &m_Image;

    void readUncompressedImageToBuffer(std::vector <uint8_t> &b, uint8_t bits);

    void readCompressedImageToBuffer(std::vector <uint8_t> &b, uint8_t bits);

public:
    bool FillTgaHeader();

    bool FillTgaImageBuffer();

    std::vector <uint8_t> GetTgaImageBuffer();
};


#endif //UBISOFT_ASSIGMENT_DECODER_H
