//
// Created by ozan on 2021-05-01.
//

#ifndef UBISOFT_ASSIGMENT_DECODER_H
#define UBISOFT_ASSIGMENT_DECODER_H

#include <fstream>
#include "tga.h"
#include <vector>
#include <functional>
#include <map>

class Decoder {

public:
    typedef void (Decoder::*bufferFunc)(std::ifstream &, std::vector<uint8_t> &, uint8_t);
    Decoder(Tga &tgaImage) : _tgaImage(tgaImage){

        _readImageToBufferMap.insert(std::make_pair(UNCOMPRESSED_TRUECOLOR_IMAGE, &Decoder::ReadCompressedImageToBuffer));
        _readImageToBufferMap.insert(std::make_pair(UNCOMPRESSED_GRAYSCALE_IMAGE, &Decoder::ReadCompressedImageToBuffer));
        _readImageToBufferMap.insert(std::make_pair(RLE_TRUECOLOR_IMAGE, &Decoder::ReadCompressedImageToBuffer));

    };

private:
//    std::function<void(std::ifstream &stream, std::vector<uint8_t> &b,
//                       uint8_t bits)>
    Tga &_tgaImage;
    std::map<TgaImageType_t, bufferFunc> _readImageToBufferMap;

    void ReadUncompressedImageToBuffer(std::ifstream &stream, std::vector<uint8_t> &buffer, uint8_t bits);

    void ReadCompressedImageToBuffer(std::ifstream &stream, std::vector<uint8_t> &buffer, uint8_t bits);

    void FillTgaHeader(std::ifstream &stream);

    void FillTgaImageBuffer(std::ifstream &stream);

    std::vector<uint8_t> GetTgaImageBuffer();

    uint32_t CalculatePixelSize(TgaHeader_t &header);

public:
    std::vector<uint8_t> Decode(std::string &fileName);
};


#endif //UBISOFT_ASSIGMENT_DECODER_H
