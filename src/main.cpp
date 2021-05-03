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

    string fileName = argv[1];
    if ((NUM_OF_REQUIRED_ARGS > argc) || (0==fileName.length()) ||  (string::npos == fileName.find(".tga"))) {
        const char *const USAGE = "Usage:\n\t\
                                    halfsize <filename.tga> \n\n\
                                    Description:\n\t\
                                    Resizes given tga image file, and save it to a new tga image file.\n";
        cout << USAGE;
        return INVALID_USAGE;
    }
    
    string fileNameWithoutExtension = fileName.substr(0, fileName.find(STRING_DELIMITER));
    ifstream inputFile(fileName, ios_base::binary);
    
    Tga originalImage;
    auto decoder = make_unique<Decoder>();
    //decoder->

    Decoder decoder(originalImage);

    inputFile.seekg(0, std::ios_base::end);
    auto fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios_base::beg);

    cout << "File Size: " << fileSize << endl;
    cout << "Header Id: " << (int) originalImage.m_Header.IDLength << endl;
    cout << "Color Map type: " << (int) originalImage.m_Header.ColorMapType << endl;
    cout << "Image type " << (int) originalImage.m_Header.ImageType << endl;
    cout << "Colormap origin: " << (int) originalImage.m_Header.ColorMapOrigin << endl;
    cout << "Colormap length: " << (int) originalImage.m_Header.ColorMapLength << endl;
    cout << "Colormap size: " << (int) originalImage.m_Header.ColorMapEntrySize << endl;

    cout << "X Origin: " << (int) originalImage.m_Header.XOrigin << endl;
    cout << "Y Origin: " << (int) originalImage.m_Header.YOrigin << endl;
    cout << "Width: " << (int) originalImage.m_Header.Width << endl;
    cout << "Height: " << (int) originalImage.m_Header.Height << endl;
    cout << "Bits: " << (int) originalImage.m_Header.Bits << endl;
    cout << "Pixel Size: " << originalImage.m_pixelSize << endl;
    cout << "Descriptor: " << (int) originalImage.m_Header.ImageDescriptor << endl;

    auto imageBuffer = decoder.Decode(fileName);
    auto processedImageBuffer = biLinearInterpolation(imageBuffer, originalImage);

    Tga newImage;
    string newFileName = fileNameWithoutExtension + PROCESSED_FILENAME_POSTFIX;
    std::ofstream outputFile( newFileName, ios_base::binary);
    Encoder encoder(outputFile, newImage);
    if (!encoder.createImageHeader(originalImage.m_Header.Width / 2, originalImage.m_Header.Height / 2, originalImage.m_Header.Bits))
        return INVALID_HEADER;
    if (!encoder.writeImageToFile(processedImageBuffer)) return CANT_WRITE_FILE;

    inputFile.close();
    outputFile.close();
    return 0;
}
