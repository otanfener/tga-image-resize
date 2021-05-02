//
// Created by ozan on 2021-05-03.
//

#include "encoder.h"


bool Encoder::createImageHeader(uint16_t width, uint16_t height, uint8_t bits) {
    m_Image.m_Header.IDLength = 0;
    m_Image.m_Header.ColorMapType = 0;
    m_Image.m_Header.ImageType = 2;
    m_Image.m_Header.ColorMapOrigin = 0;
    m_Image.m_Header.ColorMapLength = 0;
    m_Image.m_Header.ColorMapEntrySize = 0;
    m_Image.m_Header.XOrigin = 0;
    m_Image.m_Header.YOrigin = 0;
    m_Image.m_Header.Width = width;
    m_Image.m_Header.Height = height;
    m_Image.m_Header.Bits = bits;
    m_Image.m_Header.ImageDescriptor = 0;
    return true;
}
bool Encoder::writeImageToFile(std::vector<uint8_t>& b) {
    m_Stream.write((char*)&m_Image.m_Header, sizeof(m_Image.m_Header));
    std::copy(b.begin(),b.end(),std::ostreambuf_iterator<char>(m_Stream));
    m_Stream.flush();
    if(m_Stream) return true;
    else return false;
}