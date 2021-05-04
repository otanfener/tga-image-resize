//
// Created by ozan on 2021-05-02.
//

#include "image_processor.h"

std::vector<uint8_t> biLinearInterpolation(std::vector<uint8_t> &inputImage, Tga &tgaImage) {
    std::vector<uint8_t> outputImage;
    uint8_t interpolatedPixelR{0}, interpolatedPixelG{0}, interpolatedPixelB{0}, interpolatedPixelA{0};

    switch (tgaImage.pixelSize) {
        case 1:
            for (auto ix = 0; ix < tgaImage.tgaHeader.height; ix += 2) {
                for (auto iy = 0; iy < tgaImage.tgaHeader.width; iy += 2) {
                    auto jump = (tgaImage.tgaHeader.width * ix * tgaImage.pixelSize) + iy * tgaImage.pixelSize;
                    interpolatedPixelB =
                            (inputImage[jump] + inputImage[tgaImage.Seek(jump, 'R')] +
                             inputImage[tgaImage.Seek(jump, 'D')] +
                             inputImage[tgaImage.Seek(jump, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelB);
                }
            }
            break;
        case 2:
            for (auto ix = 0; ix < tgaImage.tgaHeader.height; ix += 2) {
                for (auto iy = 0; iy < tgaImage.tgaHeader.width; iy += 2) {
                    auto jump = (tgaImage.tgaHeader.width * ix * tgaImage.pixelSize) + iy * tgaImage.pixelSize;
                    interpolatedPixelB =
                            (inputImage[jump] + inputImage[tgaImage.Seek(jump, 'R')] +
                             inputImage[tgaImage.Seek(jump, 'D')] +
                             inputImage[tgaImage.Seek(jump, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelB);
                    interpolatedPixelG = (inputImage[jump + 1] + inputImage[tgaImage.Seek(jump + 1, 'R')] +
                                          inputImage[tgaImage.Seek(jump + 1, 'D')] +
                                          inputImage[tgaImage.Seek(jump + 1, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelG);
                }
            }
            break;
        case 3:
            for (auto ix = 0; ix < tgaImage.tgaHeader.height; ix += 2) {
                for (auto iy = 0; iy < tgaImage.tgaHeader.width; iy += 2) {
                    auto jump = (tgaImage.tgaHeader.width * ix * tgaImage.pixelSize) + iy * tgaImage.pixelSize;
                    interpolatedPixelB =
                            (inputImage[jump] + inputImage[tgaImage.Seek(jump, 'R')] +
                             inputImage[tgaImage.Seek(jump, 'D')] +
                             inputImage[tgaImage.Seek(jump, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelB);
                    interpolatedPixelG = (inputImage[jump + 1] + inputImage[tgaImage.Seek(jump + 1, 'R')] +
                                          inputImage[tgaImage.Seek(jump + 1, 'D')] +
                                          inputImage[tgaImage.Seek(jump + 1, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelG);
                    interpolatedPixelR = (inputImage[jump + 2] + inputImage[tgaImage.Seek(jump + 2, 'R')] +
                                          inputImage[tgaImage.Seek(jump + 2, 'D')] +
                                          inputImage[tgaImage.Seek(jump + 2, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelR);
                }
            }
            break;
        case 4:
            for (auto ix = 0; ix < tgaImage.tgaHeader.height; ix += 2) {
                for (auto iy = 0; iy < tgaImage.tgaHeader.width; iy += 2) {
                    auto jump = (tgaImage.tgaHeader.width * ix * tgaImage.pixelSize) + iy * tgaImage.pixelSize;
                    interpolatedPixelB =
                            (inputImage[jump] + inputImage[tgaImage.Seek(jump, 'R')] +
                             inputImage[tgaImage.Seek(jump, 'D')] +
                             inputImage[tgaImage.Seek(jump, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelB);
                    interpolatedPixelG = (inputImage[jump + 1] + inputImage[tgaImage.Seek(jump + 1, 'R')] +
                                          inputImage[tgaImage.Seek(jump + 1, 'D')] +
                                          inputImage[tgaImage.Seek(jump + 1, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelG);
                    interpolatedPixelR = (inputImage[jump + 2] + inputImage[tgaImage.Seek(jump + 2, 'R')] +
                                          inputImage[tgaImage.Seek(jump + 2, 'D')] +
                                          inputImage[tgaImage.Seek(jump + 2, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelR);
                    interpolatedPixelA = (inputImage[jump + 3] + inputImage[tgaImage.Seek(jump + 3, 'R')] +
                                          inputImage[tgaImage.Seek(jump + 3, 'D')] +
                                          inputImage[tgaImage.Seek(jump + 3, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelA);
                }
            }
            break;

    }
    return outputImage;
}