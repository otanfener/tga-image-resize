//
// Created by ozan on 2021-05-03.
//

#include "encoder.hpp"
#include "exception.hpp"

/// @brief Creates a new Targa image file header.
/// @param width[in] Width of the image file.
/// @param height[in] Height of the image file.
/// @param bits[in] Number of bits to denote each pixel.
/// @return Created Targa image header struct.
TgaHeader_t Encoder::CreateTgaHeader(uint16_t width, uint16_t height, uint8_t bits) {
    TgaHeader_t imageHeader;
    imageHeader.idLength = 0;
    imageHeader.colorMapType = 0;
    imageHeader.imageType = 2; //Save as uncompressed true-color image
    imageHeader.colorMapOrigin = 0;
    imageHeader.colorMapLength = 0;
    imageHeader.colorMapEntrySize = 0;
    imageHeader.xOrigin = 0;
    imageHeader.yOrigin = 0;
    imageHeader.width = width;
    imageHeader.height = height;
    imageHeader.bits = bits;
    imageHeader.imageDescriptor = 0;
    return imageHeader;
}

/// @brief Writes given Targa image header and image data to a file on the disk.
/// @param stream[in] Output stream.
/// @param imageHeader[in] Targa image header.
/// @param buffer[in] Image data.
void Encoder::WriteImageToDisk(std::ofstream &stream, TgaHeader_t &imageHeader, std::vector<uint8_t> &buffer) {
    stream.write((char *) &imageHeader, sizeof(imageHeader));
    std::copy(buffer.begin(), buffer.end(), std::ostreambuf_iterator<char>(stream));
    stream.flush();
}

/// @brief Creates a new Targa image file for given image data, dimensions, and number of bits.
/// @param fileName[in] Image file name.
/// @param imageBuffer[in] Image data.
/// @param width[in] Width of the image file.
/// @param height[in] Height of the image file.
/// @param bits[in] Number of bits to denote each pixel.
void Encoder::Encode(std::string &fileName, std::vector<uint8_t> &imageBuffer, uint16_t width, uint16_t height,
                     uint8_t bits) {
    std::ofstream stream(fileName, std::ios_base::binary);
    if (!stream.is_open()) {
        throw Exception(FILE_NOT_FOUND, "File is not found");
    }
    auto imageHeader = CreateTgaHeader(width, height, bits);
    WriteImageToDisk(stream, imageHeader, imageBuffer);
    stream.close();
}
