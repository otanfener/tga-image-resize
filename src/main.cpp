#include <iostream>
#include "main.hpp"
#include <tga.h>
#include <decoder.h>
#include <encoder.h>
#include <image_processor.h>

#define STRING_DELIMITER "."
#define PROCESSED_FILENAME_POSTFIX "_processed.tga";



int main(int argc,  const char *argv[]) {
    using namespace std;

//    string fileName = "sample1.tga";
//    if ((NUM_OF_REQUIRED_ARGS > argc) || (0==fileName.length()) ||  (string::npos == fileName.find(".tga"))) {
//        const char *const USAGE = "Usage:\n\thalfsize <filename.tga> \n\nDescription:\n\tResizes given tga image file, and save it to a new tga image file.\n";
//        cout << USAGE;
//        return INVALID_USAGE;
//    }
    
//    string fileNameWithoutExtension = fileName.substr(0, fileName.find(STRING_DELIMITER));
//    ifstream inputFile(fileName, ios_base::binary);
    
    Tga originalImage;

    Decoder decoder(originalImage);
//    decoder.Decode(fileName);
//    inputFile.seekg(0, std::ios_base::end);
//    auto fileSize = inputFile.tellg();
//    inputFile.seekg(0, std::ios_base::beg);
//
//    cout << "File Size: " << fileSize << endl;
//    cout << "Header Id: " << (int) originalImage.m_Header.IDLength << endl;
//    cout << "Color Map type: " << (int) originalImage.m_Header.ColorMapType << endl;
//    cout << "Image type " << (int) originalImage.m_Header.ImageType << endl;
//    cout << "Colormap origin: " << (int) originalImage.m_Header.ColorMapOrigin << endl;
//    cout << "Colormap length: " << (int) originalImage.m_Header.ColorMapLength << endl;
//    cout << "Colormap size: " << (int) originalImage.m_Header.ColorMapEntrySize << endl;
//
//    cout << "X Origin: " << (int) originalImage.m_Header.XOrigin << endl;
//    cout << "Y Origin: " << (int) originalImage.m_Header.YOrigin << endl;
//    cout << "Width: " << (int) originalImage.m_Header.Width << endl;
//    cout << "Height: " << (int) originalImage.m_Header.Height << endl;
//    cout << "Bits: " << (int) originalImage.m_Header.Bits << endl;
//    cout << "Pixel Size: " << originalImage.m_pixelSize << endl;
//    cout << "Descriptor: " << (int) originalImage.m_Header.ImageDescriptor << endl;

    std::string name = "sample1.tga";
    auto imageBuffer = decoder.Decode(name);
    auto processedImageBuffer = biLinearInterpolation(imageBuffer, originalImage);

    Tga newImage;
    string newFileName = "sample1_processed.tga";
    std::ofstream outputFile( newFileName, ios_base::binary);
    Encoder encoder(newImage);
    encoder.Encode(newFileName, processedImageBuffer, originalImage.tgaHeader.width / 2, originalImage.tgaHeader.height / 2, originalImage.tgaHeader.bits);

    return 0;
}
