#include <iostream>
#include <tga.h>
#include <decoder.h>
#include <encoder.h>
#include <image_processor.h>

int main(__attribute__((unused)) int argc, __attribute__((unused)) const char *argv[]) {
    std::ifstream inputFile("shuttle.tga", std::ios_base::binary);
    std::ofstream outputFile("shuttle_processed.tga", std::ios_base::binary);
    Tga oldImage;
    Decoder d(inputFile, oldImage);
    if (!inputFile.is_open()) return 1;
    if(!d.FillTgaHeader()) return 1;
    if(!d.FillTgaImageBuffer()) return 1;

    inputFile.seekg(0, std::ios_base::end);
    auto fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios_base::beg);

    std::cout<<"File Size: "<< fileSize <<std::endl;
    std::cout << "Header Id: " << (int )oldImage.m_Header.IDLength << std::endl;
    std::cout << "Color Map type: " << (int )oldImage.m_Header.ColorMapType << std::endl;
    std::cout  << "Image type " << (int )oldImage.m_Header.ImageType << std::endl;
    std::cout  << "Colormap origin: " << (int )oldImage.m_Header.ColorMapOrigin << std::endl;
    std::cout  << "Colormap length: " << (int ) oldImage.m_Header.ColorMapLength << std::endl;
    std::cout  << "Colormap size: " << (int )oldImage.m_Header.ColorMapEntrySize << std::endl;

    std::cout  << "X Origin: " << (int )oldImage.m_Header.XOrigin << std::endl;
    std::cout  << "Y Origin: " << (int )oldImage.m_Header.YOrigin << std::endl;
    std::cout  << "Width: " << (int )oldImage.m_Header.Width << std::endl;
    std::cout  << "Height: " << (int ) oldImage.m_Header.Height << std::endl;
    std::cout  << "Bits: " << (int )oldImage.m_Header.Bits << std::endl;
    std::cout << "Pixel Size: " << oldImage.m_pixelSize << std::endl;
    std::cout  << "Descriptor: " << (int ) oldImage.m_Header.ImageDescriptor << std::endl;

    auto b = d.GetTgaImageBuffer();
    auto processed = biLinearInterpolation(b, oldImage);

    Tga newImage;
    Encoder e(outputFile, newImage);
    if(!e.createImageHeader(oldImage.m_Header.Width/2, oldImage.m_Header.Height/2, oldImage.m_Header.Bits)) return 1;
    if(!e.writeImageToFile(processed)) return 1;

    inputFile.close();
    outputFile.close();
    return 0;
}
