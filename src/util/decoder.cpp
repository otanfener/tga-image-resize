//
// Created by ozan on 2021-05-01.
//

#include "decoder.h"
#include <iostream>

bool Decoder::FillTgaHeader(void) {
    m_Stream.read((char *) &m_Image.m_Header.IDLength, sizeof(m_Image.m_Header.IDLength));
    m_Stream.read((char *) &m_Image.m_Header.ColorMapType, sizeof(m_Image.m_Header.ColorMapType));
    m_Stream.read((char *) &m_Image.m_Header.ImageType, sizeof(m_Image.m_Header.ImageType));
    m_Stream.read((char *) &m_Image.m_Header.ColorMapOrigin, sizeof(m_Image.m_Header.ColorMapOrigin));
    m_Stream.read((char *) &m_Image.m_Header.ColorMapLength, sizeof(m_Image.m_Header.ColorMapLength));
    m_Stream.read((char *) &m_Image.m_Header.ColorMapEntrySize, sizeof(m_Image.m_Header.ColorMapEntrySize));
    m_Stream.read((char *) &m_Image.m_Header.XOrigin, sizeof(m_Image.m_Header.XOrigin));
    m_Stream.read((char *) &m_Image.m_Header.YOrigin, sizeof(m_Image.m_Header.YOrigin));
    m_Stream.read((char *) &m_Image.m_Header.Width, sizeof(m_Image.m_Header.Width));
    m_Stream.read((char *) &m_Image.m_Header.Height, sizeof(m_Image.m_Header.Height));
    m_Stream.read((char *) &m_Image.m_Header.Bits, sizeof(m_Image.m_Header.Bits));
    m_Stream.read((char *) &m_Image.m_Header.ImageDescriptor, sizeof(m_Image.m_Header.ImageDescriptor));

    m_Image.m_pixelSize = m_Image.m_Header.Bits/8;
    if(m_Stream) return true;
    else return false;
}

bool Decoder::FillTgaImageBuffer(void) {
    bool isSuccessful = false;
    switch (m_Image.m_Header.ImageType) {
        case 0:
            std::cout << "No image data is found!" << std::endl;
            break;
        case 1:
            std::cout << "Color mapped images are not supported!" << std::endl;
            break;
        case 2:
            std::cout << "Reading true color image" << std::endl;
            readUncompressedImageToBuffer(m_Image.m_ImageBuffer, m_Image.m_Header.Bits);
            isSuccessful = true;
            break;
        case 3:
            std::cout << "Reading grayscale  image" << std::endl;
            readUncompressedImageToBuffer(m_Image.m_ImageBuffer, m_Image.m_Header.Bits);
            isSuccessful = true;
            break;
        case 9:
            std::cout << "Color mapped encoded images are not supported!" << std::endl;
            break;
        case 10:
            std::cout<< "Reading run-length encoded image" << std::endl;
            readCompressedImageToBuffer(m_Image.m_ImageBuffer, m_Image.m_Header.Bits);
            isSuccessful = true;
            break;

    }
    return isSuccessful;

}

std::vector<uint8_t> Decoder::GetTgaImageBuffer() {
    return m_Image.m_ImageBuffer;
}

void Decoder::readUncompressedImageToBuffer(std::vector<uint8_t>& b, uint8_t bits) {
    if(bits == 16){
        //Temporary
        std::vector<uint8_t> contents((std::istreambuf_iterator<char>(m_Stream)), std::istreambuf_iterator<char>());
        b = contents;
    }else{
        std::vector<uint8_t> contents((std::istreambuf_iterator<char>(m_Stream)), std::istreambuf_iterator<char>());
        b = contents;
    }
}


void Decoder::readCompressedImageToBuffer(std::vector<uint8_t> &b, uint8_t bits) {
    uint8_t rleHeader;
    uint8_t blue, green, red, alpha;
    size_t numberOfPixels;
    switch (bits) {
        case 24:
            for (auto i = 0; i <m_Image.m_Header.Height*m_Image.m_Header.Width;) {
                m_Stream.read((char*)&rleHeader, sizeof(rleHeader));
                numberOfPixels = (rleHeader & 0x7F) + 1;
                if(rleHeader & 0x80){
                    m_Stream.read((char*)&blue, sizeof(blue));
                    m_Stream.read((char*)&green, sizeof(green));
                    m_Stream.read((char*)&red, sizeof(red));
                    for(auto j = 0;  j< numberOfPixels; j++){
                        b.push_back(blue);
                        b.push_back(green);
                        b.push_back(red);
                    }
                    i += numberOfPixels;
                }else{
                    for(auto j = 0; j< numberOfPixels; j++){
                        m_Stream.read((char*)&blue, sizeof(blue));
                        b.push_back(blue);
                        m_Stream.read((char*)&green, sizeof(green));
                        b.push_back(green);
                        m_Stream.read((char*)&red, sizeof(red));
                        b.push_back(red);
                    }
                    i+=numberOfPixels;
                }
            }
            break;
        case 32:
            for (auto i = 0; i <m_Image.m_Header.Height*m_Image.m_Header.Width;) {
                m_Stream.read((char*)&rleHeader, sizeof(rleHeader));
                numberOfPixels = (rleHeader & 0x7F) + 1;
                if(rleHeader & 0x80){
                    m_Stream.read((char*)&blue, sizeof(blue));
                    m_Stream.read((char*)&green, sizeof(green));
                    m_Stream.read((char*)&red, sizeof(red));
                    m_Stream.read((char*)&alpha, sizeof(alpha));
                    for(auto j = 0;  j< numberOfPixels; j++){
                        b.push_back(blue);
                        b.push_back(green);
                        b.push_back(red);
                        b.push_back(alpha);
                    }
                    i += numberOfPixels;
                }else{
                    for(auto j = 0; j< numberOfPixels; j++){
                        m_Stream.read((char*)&blue, sizeof(blue));
                        b.push_back(blue);
                        m_Stream.read((char*)&green, sizeof(green));
                        b.push_back(green);
                        m_Stream.read((char*)&red, sizeof(red));
                        b.push_back(red);
                        m_Stream.read((char*)&red, sizeof(alpha));
                        b.push_back(alpha);
                    }
                    i+=numberOfPixels;
                }
            }
    }
}
