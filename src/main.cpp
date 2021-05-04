#include "main.hpp"


int main(int argc, const char *argv[]) {
    using namespace std;

    if ((argc < NUM_OF_REQUIRED_ARGS)) {
        const char *const USAGE = "Usage:\n\thalfsize <filename.tga> \n\nDescription:\n\tResizes given tga image file, and save it to a new tga image file.\n";
        cout << USAGE;
        return INVALID_USAGE;
    }

    string fileName = argv[1];
    if ((0 == fileName.length()) || (string::npos == fileName.find(".tga"))) {
        std::cerr << "Invalid file" << std::endl;
        return INVALID_FILE;
    }
    
    try {
        //Decoder
        Tga originalImage;
        Decoder decoder(originalImage);
        auto imageBuffer = decoder.Decode(fileName);

        //Interpolation
        auto processedImageBuffer = biLinearInterpolation(imageBuffer, originalImage);

        //Encoder
        Tga newImage;
        string fileNameWithoutExtension = fileName.substr(0, fileName.find(STRING_DELIMITER));
        string newFileName = fileNameWithoutExtension + PROCESSED_FILENAME_POSTFIX;
        Encoder encoder(newImage);
        encoder.Encode(newFileName, processedImageBuffer, originalImage.tgaHeader.width / 2,
                       originalImage.tgaHeader.height / 2, originalImage.tgaHeader.bits);


        return SUCCESS;
    } catch (const Exception &e) {
        std::cerr << "Exception catched : " << e.what() << std::endl;
        return e.GetErrorCode();
    }
}
