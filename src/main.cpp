#include "main.hpp"


int main(int argc, const char *argv[]) {

    if ((argc < NUM_OF_REQUIRED_ARGS)) {
        const char *const USAGE = "Usage:\n\thalfsize <filename.tga> \n\nDescription:\n\tResizes given tga image file, and save it to a new tga image file.\n";
        std::cout << USAGE << std::endl;
        return static_cast<int>(StatusCode::INVALID_USAGE);
    }

    std::string fileName = argv[1];
    if ((0 == fileName.length()) || (std::string::npos == fileName.find(".tga"))) {
        std::cerr << "Invalid file\n";
        return static_cast<int>(StatusCode::INVALID_FILE);
    }

    try {
        //Decoder
        TgaImage originalImage;
        std::cout << "Reading image file: " << fileName << std::endl;
        Decoder decoder(originalImage);

        auto imageBuffer = decoder.Decode(fileName);
        std::cout << "Resizing an image with dimensions: " << originalImage.tgaHeader_.width << "x"
                  << originalImage.tgaHeader_.height << std::endl;
        //Interpolation
        auto processedImageBuffer = BiLinearInterPolation(imageBuffer, originalImage);
        std::cout << "Resizing completed, new dimensions: " << originalImage.tgaHeader_.width / 2 << "x"
                  << originalImage.tgaHeader_.height / 2 << std::endl;

        //Encoder
        TgaImage newImage;
        std::string fileNameWithoutExtension = fileName.substr(0, fileName.find(STRING_DELIMITER));
        std::string newFileName = fileNameWithoutExtension + PROCESSED_FILENAME_POSTFIX;
        Encoder encoder;

        std::cout << "Creating a new image: " << newFileName << std::endl;
        encoder.Encode(newFileName, processedImageBuffer, static_cast<uint16_t>(originalImage.tgaHeader_.width >> 1),
                       static_cast<uint16_t>(originalImage.tgaHeader_.height >> 1), originalImage.tgaHeader_.bits);

        std::cout << "Operation completed" << std::endl;
        return static_cast<int>(StatusCode::SUCCESS);
    } catch (const TgaException &e) {
        std::cerr << "TgaException catched : " << e.what() << "\n";
        return static_cast<int >(e.GetErrorCode());
    }
}
