//
// Created by ozan on 2021-05-01.
//

#include "decoder.h"
#include <iostream>

std::vector<uint8_t> Decoder::Decode(std::string &fileName){
    std::ifstream stream(fileName, std::ios_base::binary);
    if (!stream.is_open()){
        //throw error
    }
    this->FillTgaHeader(stream);
    this->CalculatePixelSize(this->_tgaImage.header);
    this->FillTgaImageBuffer(stream);
    return this->GetTgaImageBuffer();
}

void Decoder::FillTgaHeader(std::ifstream &m_Stream) {
    m_Stream.read((char *) &this->_tgaImage.header.IDLength, sizeof(this->_tgaImage.header.IDLength));
    m_Stream.read((char *) &this->_tgaImage.header.ColorMapType, sizeof(this->_tgaImage.header.ColorMapType));
    m_Stream.read((char *) &this->_tgaImage.header.ImageType, sizeof(this->_tgaImage.header.ImageType));
    m_Stream.read((char *) &this->_tgaImage.header.ColorMapOrigin, sizeof(this->_tgaImage.header.ColorMapOrigin));
    m_Stream.read((char *) &this->_tgaImage.header.ColorMapLength, sizeof(this->_tgaImage.header.ColorMapLength));
    m_Stream.read((char *) &this->_tgaImage.header.ColorMapEntrySize, sizeof(this->_tgaImage.header.ColorMapEntrySize));
    m_Stream.read((char *) &this->_tgaImage.header.XOrigin, sizeof(this->_tgaImage.header.XOrigin));
    m_Stream.read((char *) &this->_tgaImage.header.YOrigin, sizeof(this->_tgaImage.header.YOrigin));
    m_Stream.read((char *) &this->_tgaImage.header.Width, sizeof(this->_tgaImage.header.Width));
    m_Stream.read((char *) &this->_tgaImage.header.Height, sizeof(this->_tgaImage.header.Height));
    m_Stream.read((char *) &this->_tgaImage.header.Bits, sizeof(this->_tgaImage.header.Bits));
    m_Stream.read((char *) &this->_tgaImage.header.ImageDescriptor, sizeof(this->_tgaImage.header.ImageDescriptor));

}

uint32_t Decoder::CalculatePixelSize(TgaHeader_t &header){
    /* performance optimization:  (num/8) = (num>>3) */
    this->_tgaImage.pixelSize =  header.ColorMapLength == 0 ? (header.Bits >> 3) : header.ColorMapEntrySize;
    return this->_tgaImage.pixelSize; 
}



void Decoder::FillTgaImageBuffer(std::ifstream &m_Stream) {
    auto mapIter = _readImageToBufferMap.find((TgaImageType_t)this->_tgaImage.header.ImageType);
    mapIter->second(m_Stream,this->_tgaImage.buffer, this->_tgaImage.header.Bits);
}

std::vector<uint8_t> Decoder::GetTgaImageBuffer() {
    return _tgaImage.buffer;
}

void Decoder::ReadUncompressedImageToBuffer(std::ifstream &m_Stream,std::vector<uint8_t> &b, uint8_t bits) {
    std::vector<uint8_t> contents((std::istreambuf_iterator<char>(m_Stream)), std::istreambuf_iterator<char>());
    b = contents;
}

void Decoder::ReadColorMappedImageToBuffer(std::ifstream &m_Stream,std::vector<uint8_t> &b, uint8_t bits) {
    uint8_t blue, green, red, alpha;
    switch (bits) {
        case 24:
            for (auto i = 0; i < _tgaImage.header.ColorMapLength; ++i) {
                m_Stream.read((char *) &blue, sizeof(blue));
                b.push_back(blue);
                m_Stream.read((char *) &green, sizeof(green));
                b.push_back(green);
                m_Stream.read((char *) &red, sizeof(red));
                b.push_back(red);
            }
            break;
        case 32:
            for (auto i = 0; i < _tgaImage.header.ColorMapLength; ++i) {
                m_Stream.read((char *) &blue, sizeof(blue));
                b.push_back(blue);
                m_Stream.read((char *) &green, sizeof(green));
                b.push_back(green);
                m_Stream.read((char *) &red, sizeof(red));
                b.push_back(red);
                m_Stream.read((char *) &alpha, sizeof(alpha));
                b.push_back(alpha);
            }
            break;
    }

}

void Decoder::ReadCompressedImageToBuffer(std::ifstream &m_Stream,std::vector<uint8_t> &b, uint8_t bits) {
    uint8_t rleHeader;
    size_t numberOfPixels;
    size_t channelSize = (bits>>3);
    uint8_t channelBuf[channelSize];

    for (auto i = 0; i <_tgaImage.header.Height * _tgaImage.header.Width;) {
                m_Stream.read((char *) &rleHeader, sizeof(rleHeader));
                numberOfPixels = (rleHeader & 0x7F) + 1; // Extract repetition for the packet
                if (rleHeader & 0x80) { //Determine if it's RLE packet or normal packet
                    m_Stream.read((char *) &channelBuf[0], channelSize);
                    for (auto j = 0; j < numberOfPixels; j++) {
                        for(auto k=0;k<channelSize; k++){
                            b.push_back(channelBuf[k]);
                        }
                    }
                    i += numberOfPixels;
                } else {
                    for (auto j = 0; j < numberOfPixels; j++) {
                        m_Stream.read((char *) &channelBuf[k], channelSize);
                        for(auto k=0;k<channelSize; k++){
                            b.push_back(channelBuf[k]);
                        }
                    }
                    i += numberOfPixels;
                }
            }
    
}
