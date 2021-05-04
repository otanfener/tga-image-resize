#include "main.hpp"


int main(int argc, const char *argv[]) {

    if ((argc < NUM_OF_REQUIRED_ARGS)) {
        const char *const USAGE = "Usage:\n\thalfsize <filename.tga> \n\nDescription:\n\tResizes given tga image file, and save it to a new tga image file.\n";
        std::cout << USAGE << std::endl;
        return INVALID_USAGE;
    }

    std::string fileName = argv[1];
    if ((0 == fileName.length()) || (std::string::npos == fileName.find(".tga"))) {
        std::cerr << "Invalid file" << std::endl;
        return INVALID_FILE;
    }

    try {
        //Decoder
        TgaImage originalImage;
        Decoder decoder(originalImage);
        auto imageBuffer = decoder.Decode(fileName);

        //Interpolation
        auto processedImageBuffer = BiLinearInterPolation(imageBuffer, originalImage);

        //Encoder
        TgaImage newImage;
        std::string fileNameWithoutExtension = fileName.substr(0, fileName.find(STRING_DELIMITER));
        std::string newFileName = fileNameWithoutExtension + PROCESSED_FILENAME_POSTFIX;
        Encoder encoder(newImage);
        encoder.Encode(newFileName, processedImageBuffer, originalImage.tgaHeader_.width / 2,
                       originalImage.tgaHeader_.height / 2, originalImage.tgaHeader_.bits);


        return SUCCESS;
    } catch (const TgaException &e) {
        std::cerr << "TgaException catched : " << e.what();
        return e.GetErrorCode();
    }
}
