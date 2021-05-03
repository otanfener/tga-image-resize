//
// Created by ozan on 2021-05-01.
//

#ifndef UBISOFT_ASSIGMENT_DECODER_H
#define UBISOFT_ASSIGMENT_DECODER_H

#include <fstream>
#include "tga.h"
#include <vector>
#include <function>
#include <unordered_map>

class Decoder {
public:
    Decoder(Tga &tgaImage) : _tgaImage(tgaImage),  _readImageToBufferMap{}{
        _readImageToBufferMap[TGA_IMAGE_TYPE_TRUE_COLOR] = ReadUncompressedImageToBuffer;
        _readImageToBufferMap[TGA_IMAGE_TYPE_GRAYSCALE] = ReadUncompressedImageToBuffer;
        _readImageToBufferMap[TGA_IMAGE_RUN_LEN] = ReadCompressedImageToBuffer;
        
    };

private:

    Tga &_tgaImage;
    
    std::unordered_map<TgaImageType_t,std::function<void(std::ifstream &m_Stream,std::vector <uint8_t> &b, uint8_t bits)>> _readImageToBufferMap;   

    void ReadUncompressedImageToBuffer(std::ifstream &m_Stream,std::vector <uint8_t> &b, uint8_t bits);
    void ReadCompressedImageToBuffer(std::ifstream &m_Stream,std::vector <uint8_t> &b, uint8_t bits);
    void ReadColorMappedImageToBuffer(std::ifstream &m_Stream,std::vector<uint8_t> &b, uint8_t bits);

    void FillTgaHeader(std::ifstream &m_Stream);
    void FillTgaImageBuffer(std::ifstream &m_Stream);
    std::vector <uint8_t> GetTgaImageBuffer();
    uint32_t CalculatePixelSize(TgaHeader_t &header);

public:

    std::vector<uint8_t> Decode(std::string& fileName);
    
};


#endif //UBISOFT_ASSIGMENT_DECODER_H
