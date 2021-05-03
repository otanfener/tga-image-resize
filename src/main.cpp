#include <iostream>
#include <tga.h>
#include <decoder.h>
#include <encoder.h>
#include <image_processor.h>

using namespace std;
static const char *const USAGE = "Usage:\n\thalfsize <filename.tga> \n\nDescription:\n\tResizes given tga image file, and save it to a new tga image file.\n";

int main(int argc,  const char *argv[]) {

    if (argc < 2) {
        cout << USAGE;
        return 1;
    }
    string filename = argv[1];
    std::ifstream inputFile(filename, std::ios_base::binary);
    std::ofstream outputFile(filename + "_processed.tga", std::ios_base::binary);
    Tga oldImage;
    Decoder d(inputFile, oldImage);
    if (!inputFile.is_open()) return 1;
    if (!d.FillTgaHeader()) return 1;
    if (!d.FillTgaImageBuffer()) return 1;

    inputFile.seekg(0, std::ios_base::end);
    auto fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios_base::beg);

    cout << "File Size: " << fileSize << endl;
    cout << "Header Id: " << (int) oldImage.m_Header.IDLength << endl;
    cout << "Color Map type: " << (int) oldImage.m_Header.ColorMapType << endl;
    cout << "Image type " << (int) oldImage.m_Header.ImageType << endl;
    cout << "Colormap origin: " << (int) oldImage.m_Header.ColorMapOrigin << endl;
    cout << "Colormap length: " << (int) oldImage.m_Header.ColorMapLength << endl;
    cout << "Colormap size: " << (int) oldImage.m_Header.ColorMapEntrySize << endl;

    cout << "X Origin: " << (int) oldImage.m_Header.XOrigin << endl;
    cout << "Y Origin: " << (int) oldImage.m_Header.YOrigin << endl;
    cout << "Width: " << (int) oldImage.m_Header.Width << endl;
    cout << "Height: " << (int) oldImage.m_Header.Height << endl;
    cout << "Bits: " << (int) oldImage.m_Header.Bits << endl;
    cout << "Pixel Size: " << oldImage.m_pixelSize << endl;
    cout << "Descriptor: " << (int) oldImage.m_Header.ImageDescriptor << endl;

    auto b = d.GetTgaImageBuffer();
    auto processed = biLinearInterpolation(b, oldImage);

    Tga newImage;
    Encoder e(outputFile, newImage);
    if (!e.createImageHeader(oldImage.m_Header.Width / 2, oldImage.m_Header.Height / 2, oldImage.m_Header.Bits))
        return 1;
    if (!e.writeImageToFile(processed)) return 1;

    inputFile.close();
    outputFile.close();
    return 0;
}
