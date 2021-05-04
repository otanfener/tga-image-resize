//
// Created by ozan on 2021-05-01.
//

#include "decoder.hpp"
#include "exception.hpp"
#include <iostream>


/// @brief Reads a Targa image file from the disk, and returns underlying image data.
/// @param fileName[in] Image file name.
/// @return Image data as vector of bytes.

static constexpr int DIVIDE_HALF = 3;

std::vector<uint8_t> Decoder::Decode(std::string &fileName) {
    std::ifstream stream(fileName, std::ios_base::binary);
    if (!stream.is_open()) {
        throw TgaException(static_cast<uint32_t>(StatusCode::FILE_NOT_FOUND), "File is not found");
    }
    FillTgaHeader(stream);
    CalculatePixelSize(tgaImage_.tgaHeader_);
    FillTgaImageBuffer(stream);
    return GetTgaImageBuffer();
}

/// @brief Reads Targa image header section from the file.
/// @param stream[in] Input stream.
void Decoder::FillTgaHeader(std::ifstream &stream) {
    stream.read((char *) &tgaImage_.tgaHeader_.idLength, sizeof(tgaImage_.tgaHeader_.idLength));
    stream.read((char *) &tgaImage_.tgaHeader_.colorMapType, sizeof(tgaImage_.tgaHeader_.colorMapType));
    stream.read((char *) &tgaImage_.tgaHeader_.imageType, sizeof(tgaImage_.tgaHeader_.imageType));
    stream.read((char *) &tgaImage_.tgaHeader_.colorMapOrigin, sizeof(tgaImage_.tgaHeader_.colorMapOrigin));
    stream.read((char *) &tgaImage_.tgaHeader_.colorMapLength, sizeof(tgaImage_.tgaHeader_.colorMapLength));
    stream.read((char *) &tgaImage_.tgaHeader_.colorMapEntrySize, sizeof(tgaImage_.tgaHeader_.colorMapEntrySize));
    stream.read((char *) &tgaImage_.tgaHeader_.xOrigin, sizeof(tgaImage_.tgaHeader_.xOrigin));
    stream.read((char *) &tgaImage_.tgaHeader_.yOrigin, sizeof(tgaImage_.tgaHeader_.yOrigin));
    stream.read((char *) &tgaImage_.tgaHeader_.width, sizeof(tgaImage_.tgaHeader_.width));
    stream.read((char *) &tgaImage_.tgaHeader_.height, sizeof(tgaImage_.tgaHeader_.height));
    stream.read((char *) &tgaImage_.tgaHeader_.bits, sizeof(tgaImage_.tgaHeader_.bits));
    stream.read((char *) &tgaImage_.tgaHeader_.imageDescriptor, sizeof(tgaImage_.tgaHeader_.imageDescriptor));

}

/// @brief Calculates image pixel size.
/// @param header[in] Targa image header.
/// @return Calculated pixel size as unsigned integer.
uint32_t Decoder::CalculatePixelSize(TgaHeader_t &header) {
    /* performance optimization:  (num/8) = (num>>3) */
    tgaImage_.pixelSize_ = header.colorMapLength == 0 ? (header.bits >> DIVIDE_HALF) : header.colorMapEntrySize;
    return tgaImage_.pixelSize_;
}

/// @brief Reads image data from disk to a buffer.
/// @param stream[in] Input stream.
void Decoder::FillTgaImageBuffer(std::ifstream &stream) {
    if (tgaImage_.tgaHeader_.imageType == static_cast<uint8_t>(TgaImageType::UNCOMPRESSED_TRUECOLOR_IMAGE) ||
        tgaImage_.tgaHeader_.imageType == static_cast<uint8_t>(TgaImageType::UNCOMPRESSED_GRAYSCALE_IMAGE) ||
        tgaImage_.tgaHeader_.imageType == static_cast<uint8_t>(TgaImageType::RLE_TRUECOLOR_IMAGE)) {
        auto mapIter = readImageToBufferMap_.find((TgaImageType) tgaImage_.tgaHeader_.imageType);

        (this->*mapIter->second)(stream, tgaImage_.imageBuffer_, tgaImage_.tgaHeader_.bits);
    } else {
        throw TgaException(static_cast<uint32_t>(StatusCode::INVALID_HEADER), "Invalid image type");
    }

}

///
/// @return Returns image data as a vector of bytes.
std::vector<uint8_t> Decoder::GetTgaImageBuffer() {
    return tgaImage_.imageBuffer_;
}

/// @brief Reads true color Targa image data from disk to a buffer.
/// @param stream[in] Input stream.
/// @param buffer[in,out] Image buffer to be filled.
/// @param bits[in] Number of bits denoting each pixel.
void Decoder::ReadUncompressedImageToBuffer(std::ifstream &stream, std::vector<uint8_t> &buffer, uint8_t bits) {
    std::vector<uint8_t> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    buffer = contents;
}

/// @brief Reads RLE encoded Targa image data from disk to a buffer.
/// @param stream[in] Input stream.
/// @param buffer[in,out] Image buffer to be filled.
/// @param bits[in] Number of bits denoting each pixel.
void Decoder::ReadCompressedImageToBuffer(std::ifstream &stream, std::vector<uint8_t> &buffer, uint8_t bits) {
    uint8_t rleHeader;
    size_t numberOfPixels;
    size_t channelSize = (bits >> DIVIDE_HALF);
    uint8_t channelBuf[channelSize];
    size_t imageSize = tgaImage_.tgaHeader_.height * tgaImage_.tgaHeader_.width;

    for (auto i = 0; i < imageSize;) {
        stream.read((char *) &rleHeader, sizeof(rleHeader));
        numberOfPixels = (rleHeader & static_cast<uint8_t>(TgaBitMask::RLE_LENGTH_BITMASK)) +
                         1; // Extract repetition for the packet
        if (rleHeader &
            static_cast<uint8_t>(TgaBitMask::RLE_CHUNK_BITMASK)) { //Determine if it's RLE packet or normal packet
            stream.read((char *) &channelBuf[0], channelSize);
            for (auto j = 0; j < numberOfPixels; j++) {
                for (auto k = 0; k < channelSize; k++) {
                    buffer.push_back(channelBuf[k]);
                }
            }
            i += numberOfPixels;
        } else {
            for (auto j = 0; j < numberOfPixels; j++) {
                stream.read((char *) &channelBuf[0], channelSize);
                for (auto k = 0; k < channelSize; k++) {
                    buffer.push_back(channelBuf[k]);
                }
            }
            i += numberOfPixels;
        }
    }

}
