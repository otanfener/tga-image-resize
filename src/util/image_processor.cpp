//
// Created by ozan on 2021-05-02.
//

#include "image_processor.hpp"

std::vector<uint8_t> biLinearInterpolation(std::vector<uint8_t> &inputImage, Tga &tgaImage) {
    std::vector<uint8_t> outputImage;
    uint8_t interpolatedPixel;
    for (auto ix = 0; ix < tgaImage.tgaHeader.height; ix += 2) {
        for (auto iy = 0; iy < tgaImage.tgaHeader.width; iy += 2) {
            auto jump = (tgaImage.tgaHeader.width * ix * tgaImage.pixelSize) + iy * tgaImage.pixelSize;
            for(auto ij = 0; ij <tgaImage.pixelSize; ij++){
                interpolatedPixel =
                        (inputImage[jump + ij] + inputImage[tgaImage.Seek(jump + ij, 'R')] +
                         inputImage[tgaImage.Seek(jump + ij, 'D')] +
                         inputImage[tgaImage.Seek(jump + ij, 'X')]) / 4;
                outputImage.push_back(interpolatedPixel);
            }

        }
    }
    return outputImage;
}