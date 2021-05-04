//
// Created by ozan on 2021-05-02.
//

#ifndef UBISOFT_ASSIGMENT_IMAGE_PROCESSOR_HPP
#define UBISOFT_ASSIGMENT_IMAGE_PROCESSOR_HPP

#include "tga.hpp"
#include <cstdint>
#include <vector>
std::vector <uint8_t> biLinearInterpolation(std::vector <uint8_t> &inputImage, Tga &tgaImage);

#endif //UBISOFT_ASSIGMENT_IMAGE_PROCESSOR_HPP
