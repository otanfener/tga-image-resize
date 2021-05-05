//
// Created by ozan on 2021-05-01.
//

#ifndef UBISOFT_ASSIGMENT_DECODER_HPP
#define UBISOFT_ASSIGMENT_DECODER_HPP

#include <fstream>
#include "tga.hpp"
#include <vector>
#include <functional>
#include <unordered_map>
#include <cstdint>

class Decoder {

public:
    typedef void (Decoder::*bufferFunc)(std::ifstream &, std::vector<uint8_t> &, uint8_t);

    /// @brief Builds a decoder object for a given tga image object.
    /// @param tgaImage TgaImage image object
    explicit Decoder(TgaImage &tgaImage) : tgaImage_(tgaImage) {

        readImageToBufferMap_[TgaImageType::UNCOMPRESSED_TRUECOLOR_IMAGE] = &Decoder::ReadUncompressedImageToBuffer;
        readImageToBufferMap_[TgaImageType::UNCOMPRESSED_GRAYSCALE_IMAGE] = &Decoder::ReadUncompressedImageToBuffer;
        readImageToBufferMap_[TgaImageType::RLE_TRUECOLOR_IMAGE] = &Decoder::ReadCompressedImageToBuffer;
        readImageToBufferMap_[TgaImageType::RLE_GRAYSCALE_IMAGE] = &Decoder::ReadCompressedImageToBuffer;

    };

private:
    TgaImage &tgaImage_;
    std::unordered_map<TgaImageType, bufferFunc> readImageToBufferMap_;

    void ReadUncompressedImageToBuffer(std::ifstream &stream, std::vector<uint8_t> &buffer, uint8_t bits);

    void ReadCompressedImageToBuffer(std::ifstream &stream, std::vector<uint8_t> &buffer, uint8_t bits);

    void FillTgaHeader(std::ifstream &stream);

    void FillTgaImageBuffer(std::ifstream &stream);

    std::vector<uint8_t> GetTgaImageBuffer() const;

    uint32_t CalculatePixelSize(TgaHeader_t &header);

public:
    std::vector<uint8_t> Decode(const std::string &fileName);
};


#endif //UBISOFT_ASSIGMENT_DECODER_HPP
