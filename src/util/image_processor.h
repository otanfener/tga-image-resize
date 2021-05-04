//
// Created by ozan on 2021-05-02.
//

#ifndef UBISOFT_ASSIGMENT_IMAGE_PROCESSOR_H
#define UBISOFT_ASSIGMENT_IMAGE_PROCESSOR_H

#include "tga.h"
#include <cstdint>
#include <vector>
std::vector <uint8_t> biLinearInterpolation(std::vector <uint8_t> &inputImage, Tga &tgaImage);

#endif //UBISOFT_ASSIGMENT_IMAGE_PROCESSOR_H
