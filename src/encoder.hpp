//
// Created by ozan on 2021-05-03.
//

#ifndef UBISOFT_ASSIGMENT_ENCODER_HPP
#define UBISOFT_ASSIGMENT_ENCODER_HPP

#include "tga.hpp"
#include <fstream>
#include <vector>
#include <cstdint>

class Encoder {
public:
    /// @brief Builds an encoder object for a given tga image object.
    /// @param tgaImage TgaImage image object
    Encoder(TgaImage &tgaImage) : tgaImage_(tgaImage) {};

private:
    TgaImage &tgaImage_;

    TgaHeader_t CreateTgaHeader(uint16_t width, uint16_t height, uint8_t bits);

    void WriteImageToDisk(std::ofstream &stream, TgaHeader_t &imageHeader, std::vector<uint8_t> &buffer);

public:
    void
    Encode(std::string &fileName, std::vector<uint8_t> &imageBuffer, uint16_t width, uint16_t height, uint8_t bits);

};


#endif //UBISOFT_ASSIGMENT_ENCODER_HPP
