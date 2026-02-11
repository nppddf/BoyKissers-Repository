#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "../inc/xor_cipher_utils.hpp"

int main(int argc, char* argv[])
{
    if(argc != 5)
    {
        std::cout << "Usage: " << argv[0]
                  << " <encrypt|decrypt> <input_path> <output_path> <key>\n";
        return 1;
    }

    try
    {
        std::string mode = argv[1];
        std::string inputPath = argv[2];
        std::string outputPath = argv[3];
        std::string key = argv[4];

        std::vector<uint8_t> inputData = xor_cipher::readBinaryFile(inputPath);
        std::string inputText(inputData.begin(), inputData.end());

        std::string outputText;
        if(mode == "encrypt")
            outputText = xor_cipher::encryptText(inputText, key);
        else if(mode == "decrypt")
            outputText = xor_cipher::decryptText(inputText, key);
        else
        {
            std::cout << "Unknown mode: " << mode << '\n';
            return 1;
        }

        std::vector<uint8_t> outputData(outputText.begin(), outputText.end());
        xor_cipher::writeBinaryFile(outputPath, outputData);

        std::cout << "Done. Wrote " << outputData.size() << " bytes to "
                  << outputPath << ".\n";
    }
    catch(const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
