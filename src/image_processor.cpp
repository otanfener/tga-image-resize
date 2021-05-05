//
// Created by ozan on 2021-05-02.
//

#include "image_processor.hpp"

///
/// @brief Applies bilinear interpolation to the given image buffer.
/// @param inputImage[in] Image buffer to be interpolated
/// @param tgaImage[in]  Tga image object
/// @return Processed image buffer as vector of bytes.
std::vector<uint8_t> BiLinearInterPolation(std::vector<uint8_t> &inputImage, TgaImage &tgaImage) {
    std::vector<uint8_t> outputImage;
    uint8_t interpolatedPixel;
    for (auto ix = 0; ix < tgaImage.tgaHeader_.height - 1; ix += 2) {
        for (auto iy = 0; iy < tgaImage.tgaHeader_.width - 1; iy += 2) {
            auto jump = (tgaImage.tgaHeader_.width * ix * tgaImage.pixelSize_) + iy * tgaImage.pixelSize_;
            for (uint32_t ij = 0; ij < tgaImage.pixelSize_; ij++) {
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