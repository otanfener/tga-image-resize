//
// Created by ozan on 2021-05-01.
//

#include "decoder.hpp"
#include "exception.hpp"
#include <iostream>


/// @brief Reads a Targa image file from the disk, and returns underlying image data.
/// @param fileName[in] Image file name.
/// @return Image data as vector of bytes.
std::vector<uint8_t> Decoder::Decode(std::string &fileName) {
    std::ifstream stream(fileName, std::ios_base::binary);
    if (!stream.is_open()) {
        throw Exception(FILE_NOT_FOUND, "File is not found");
    }
    FillTgaHeader(stream);
    CalculatePixelSize(_tgaImage.tgaHeader);
    FillTgaImageBuffer(stream);
    return GetTgaImageBuffer();
}

/// @brief Reads Targa image header section from the file.
/// @param stream[in] Input stream.
void Decoder::FillTgaHeader(std::ifstream &stream) {
    stream.read((char *) &_tgaImage.tgaHeader.idLength, sizeof(_tgaImage.tgaHeader.idLength));
    stream.read((char *) &_tgaImage.tgaHeader.colorMapType, sizeof(_tgaImage.tgaHeader.colorMapType));
    stream.read((char *) &_tgaImage.tgaHeader.imageType, sizeof(_tgaImage.tgaHeader.imageType));
    stream.read((char *) &_tgaImage.tgaHeader.colorMapOrigin, sizeof(_tgaImage.tgaHeader.colorMapOrigin));
    stream.read((char *) &_tgaImage.tgaHeader.colorMapLength, sizeof(_tgaImage.tgaHeader.colorMapLength));
    stream.read((char *) &_tgaImage.tgaHeader.colorMapEntrySize, sizeof(_tgaImage.tgaHeader.colorMapEntrySize));
    stream.read((char *) &_tgaImage.tgaHeader.xOrigin, sizeof(_tgaImage.tgaHeader.xOrigin));
    stream.read((char *) &_tgaImage.tgaHeader.yOrigin, sizeof(_tgaImage.tgaHeader.yOrigin));
    stream.read((char *) &_tgaImage.tgaHeader.width, sizeof(_tgaImage.tgaHeader.width));
    stream.read((char *) &_tgaImage.tgaHeader.height, sizeof(_tgaImage.tgaHeader.height));
    stream.read((char *) &_tgaImage.tgaHeader.bits, sizeof(_tgaImage.tgaHeader.bits));
    stream.read((char *) &_tgaImage.tgaHeader.imageDescriptor, sizeof(_tgaImage.tgaHeader.imageDescriptor));

}

/// @brief Calculates image pixel size.
/// @param header[in] Targa image header.
/// @return Calculated pixel size as unsigned integer.
uint32_t Decoder::CalculatePixelSize(TgaHeader_t &header) {
    /* performance optimization:  (num/8) = (num>>3) */
    _tgaImage.pixelSize = header.colorMapLength == 0 ? (header.bits >> 3) : header.colorMapEntrySize;
    return _tgaImage.pixelSize;
}

/// @brief Reads image data from disk to a buffer.
/// @param stream[in] Input stream.
void Decoder::FillTgaImageBuffer(std::ifstream &stream) {
    if (_tgaImage.tgaHeader.imageType == UNCOMPRESSED_TRUECOLOR_IMAGE ||
        _tgaImage.tgaHeader.imageType == UNCOMPRESSED_GRAYSCALE_IMAGE ||
        _tgaImage.tgaHeader.imageType == RLE_TRUECOLOR_IMAGE) {
        auto mapIter = _readImageToBufferMap.find((TgaImageType_t) _tgaImage.tgaHeader.imageType);

        (this->*mapIter->second)(stream, _tgaImage.imageBuffer, _tgaImage.tgaHeader.bits);
    } else {
        throw Exception(INVALID_HEADER, "Invalid image type");
    }

}

///
/// @return Returns image data as a vector of bytes.
std::vector<uint8_t> Decoder::GetTgaImageBuffer() {
    return _tgaImage.imageBuffer;
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
    size_t channelSize = (bits >> 3);
    uint8_t channelBuf[channelSize];
    size_t imageSize = _tgaImage.tgaHeader.height * _tgaImage.tgaHeader.width;

    for (auto i = 0; i < imageSize;) {
        stream.read((char *) &rleHeader, sizeof(rleHeader));
        numberOfPixels = (rleHeader & RLE_LENGTH_BITMASK) + 1; // Extract repetition for the packet
        if (rleHeader & RLE_CHUNK_BITMASK) { //Determine if it's RLE packet or normal packet
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
