//
// Created by ozan on 2021-05-01.
//

#include "decoder.h"

std::vector<uint8_t> Decoder::Decode(std::string &fileName) {
    std::ifstream stream(fileName, std::ios_base::binary);
    if (!stream.is_open()) {
        //throw error
    }
    FillTgaHeader(stream);
    CalculatePixelSize(_tgaImage.tgaHeader);
    FillTgaImageBuffer(stream);
    return GetTgaImageBuffer();
}

void Decoder::FillTgaHeader(std::ifstream &stream) {
    stream.read((char *) &_tgaImage.tgaHeader.idLength, sizeof(_tgaImage.tgaHeader.idLength));
    stream.read((char *) &_tgaImage.tgaHeader.colorMapType, sizeof(_tgaImage.tgaHeader.colorMapType));
    stream.read((char *) &_tgaImage.tgaHeader.imageType, sizeof(_tgaImage.tgaHeader.imageType));
    stream.read((char *) &_tgaImage.tgaHeader.colorMapOrigin, sizeof(_tgaImage.tgaHeader.colorMapOrigin));
    stream.read((char *) &_tgaImage.tgaHeader.colorMapLength, sizeof(_tgaImage.tgaHeader.colorMapLength));
    stream.read((char *) &_tgaImage.tgaHeader.colorMapEntrySize,sizeof(_tgaImage.tgaHeader.colorMapEntrySize));
    stream.read((char *) &_tgaImage.tgaHeader.xOrigin, sizeof(_tgaImage.tgaHeader.xOrigin));
    stream.read((char *) &_tgaImage.tgaHeader.yOrigin, sizeof(_tgaImage.tgaHeader.yOrigin));
    stream.read((char *) &_tgaImage.tgaHeader.width, sizeof(_tgaImage.tgaHeader.width));
    stream.read((char *) &_tgaImage.tgaHeader.height, sizeof(_tgaImage.tgaHeader.height));
    stream.read((char *) &_tgaImage.tgaHeader.bits, sizeof(_tgaImage.tgaHeader.bits));
    stream.read((char *) &_tgaImage.tgaHeader.imageDescriptor, sizeof(_tgaImage.tgaHeader.imageDescriptor));

}

uint32_t Decoder::CalculatePixelSize(TgaHeader_t &header) {
    /* performance optimization:  (num/8) = (num>>3) */
    _tgaImage.pixelSize = header.colorMapLength == 0 ? (header.bits >> 3) : header.colorMapEntrySize;
    return _tgaImage.pixelSize;
}


void Decoder::FillTgaImageBuffer(std::ifstream &stream) {
    auto mapIter = _readImageToBufferMap[(TgaImageType_t) _tgaImage.tgaHeader.imageType];
    (this->*mapIter)(stream, _tgaImage.imageBuffer, _tgaImage.tgaHeader.bits);
}

std::vector<uint8_t> Decoder::GetTgaImageBuffer() {
    return _tgaImage.imageBuffer;
}

void Decoder::ReadUncompressedImageToBuffer(std::ifstream &stream, std::vector<uint8_t> &buffer, uint8_t bits) {
    std::vector<uint8_t> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    buffer = contents;
}


void Decoder::ReadCompressedImageToBuffer(std::ifstream &stream, std::vector<uint8_t> &buffer, uint8_t bits) {
    uint8_t rleHeader;
    size_t numberOfPixels;
    size_t channelSize = (bits >> 3);
    uint8_t channelBuf[channelSize];
    size_t imageSize = _tgaImage.tgaHeader.height * _tgaImage.tgaHeader.width;

    for (auto i = 0; i < imageSize;) {
        stream.read((char *) &rleHeader, sizeof(rleHeader));
        numberOfPixels = (rleHeader & 0x7F) + 1; // Extract repetition for the packet
        if (rleHeader & 0x80) { //Determine if it's RLE packet or normal packet
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
