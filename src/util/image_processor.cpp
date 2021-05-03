//
// Created by ozan on 2021-05-02.
//

#include "tga.h"

std::vector <uint8_t> biLinearInterpolation(std::vector <uint8_t> &inputImage, Tga &t) {
    std::vector <uint8_t> outputImage;
    uint8_t interpolatedPixelR{0}, interpolatedPixelG{0}, interpolatedPixelB{0}, interpolatedPixelA{0};

    switch (t.m_pixelSize) {
        case 1:
            for (auto ix = 0; ix < t.m_Header.Height; ix += 2) {
                for (auto iy = 0; iy < t.m_Header.Width; iy += 2) {
                    auto jump = (t.m_Header.Width * ix * t.m_pixelSize) + iy * t.m_pixelSize;
                    interpolatedPixelB =
                            (inputImage[jump] + inputImage[t.Move(jump, 'R')] + inputImage[t.Move(jump, 'D')] +
                             inputImage[t.Move(jump, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelB);
                }
            }
            break;
        case 2:
            for (auto ix = 0; ix < t.m_Header.Height; ix += 2) {
                for (auto iy = 0; iy < t.m_Header.Width; iy += 2) {
                    auto jump = (t.m_Header.Width * ix * t.m_pixelSize) + iy * t.m_pixelSize;
                    interpolatedPixelB =
                            (inputImage[jump] + inputImage[t.Move(jump, 'R')] + inputImage[t.Move(jump, 'D')] +
                             inputImage[t.Move(jump, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelB);
                    interpolatedPixelG = (inputImage[jump + 1] + inputImage[t.Move(jump + 1, 'R')] +
                                          inputImage[t.Move(jump + 1, 'D')] + inputImage[t.Move(jump + 1, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelG);
                }
            }
            break;
        case 3:
            for (auto ix = 0; ix < t.m_Header.Height; ix += 2) {
                for (auto iy = 0; iy < t.m_Header.Width; iy += 2) {
                    auto jump = (t.m_Header.Width * ix * t.m_pixelSize) + iy * t.m_pixelSize;
                    interpolatedPixelB =
                            (inputImage[jump] + inputImage[t.Move(jump, 'R')] + inputImage[t.Move(jump, 'D')] +
                             inputImage[t.Move(jump, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelB);
                    interpolatedPixelG = (inputImage[jump + 1] + inputImage[t.Move(jump + 1, 'R')] +
                                          inputImage[t.Move(jump + 1, 'D')] + inputImage[t.Move(jump + 1, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelG);
                    interpolatedPixelR = (inputImage[jump + 2] + inputImage[t.Move(jump + 2, 'R')] +
                                          inputImage[t.Move(jump + 2, 'D')] + inputImage[t.Move(jump + 2, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelR);
                }
            }
            break;
        case 4:
            for (auto ix = 0; ix < t.m_Header.Height; ix += 2) {
                for (auto iy = 0; iy < t.m_Header.Width; iy += 2) {
                    auto jump = (t.m_Header.Width * ix * t.m_pixelSize) + iy * t.m_pixelSize;
                    interpolatedPixelB =
                            (inputImage[jump] + inputImage[t.Move(jump, 'R')] + inputImage[t.Move(jump, 'D')] +
                             inputImage[t.Move(jump, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelB);
                    interpolatedPixelG = (inputImage[jump + 1] + inputImage[t.Move(jump + 1, 'R')] +
                                          inputImage[t.Move(jump + 1, 'D')] + inputImage[t.Move(jump + 1, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelG);
                    interpolatedPixelR = (inputImage[jump + 2] + inputImage[t.Move(jump + 2, 'R')] +
                                          inputImage[t.Move(jump + 2, 'D')] + inputImage[t.Move(jump + 2, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelR);
                    interpolatedPixelA = (inputImage[jump + 3] + inputImage[t.Move(jump + 3, 'R')] +
                                          inputImage[t.Move(jump + 3, 'D')] + inputImage[t.Move(jump + 3, 'X')]) / 4;
                    outputImage.push_back(interpolatedPixelA);
                }
            }
            break;

    }
    return outputImage;
}