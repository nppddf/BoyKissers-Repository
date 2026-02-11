#include "../inc/xor_cipher_utils.hpp"

#include <fstream>
#include <stdexcept>

namespace xor_cipher {

std::vector<uint8_t> readBinaryFile(const std::string& path)
{
    if(path.empty())
        throw std::invalid_argument("File path is empty.");

    std::ifstream file(path, std::ios::binary);
    if(!file)
        throw std::runtime_error("Failed to open file for reading: " + path);

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    if(size < 0)
        throw std::runtime_error("Failed to get file size: " + path);

    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> data(static_cast<size_t>(size));
    if(size > 0 && !file.read(reinterpret_cast<char*>(data.data()), size))
        throw std::runtime_error("Failed to read file: " + path);

    return data;
}

void writeBinaryFile(const std::string& path, const std::vector<uint8_t>& data)
{
    if(path.empty())
        throw std::invalid_argument("File path is empty.");

    std::ofstream file(path, std::ios::binary);
    if(!file)
        throw std::runtime_error("Failed to open file for writing: " + path);

    if(!data.empty())
    {
        file.write(reinterpret_cast<const char*>(data.data()),
                   static_cast<std::streamsize>(data.size()));
        if(!file)
            throw std::runtime_error("Failed to write file: " + path);
    }
}

static std::string applyXorCipher(const std::string& text,
                                  const std::string& key)
{
    if(key.empty())
        throw std::invalid_argument("Key must not be empty.");

    std::string result;
    result.resize(text.size());

    for(size_t i = 0; i < text.size(); ++i)
    {
        unsigned char textByte = static_cast<unsigned char>(text[i]);
        unsigned char keyByte =
            static_cast<unsigned char>(key[i % key.size()]);
        result[i] = static_cast<char>(textByte ^ keyByte);
    }

    return result;
}

std::string encryptText(const std::string& text, const std::string& key)
{
    return applyXorCipher(text, key);
}

std::string decryptText(const std::string& text, const std::string& key)
{
    return applyXorCipher(text, key);
}

}  // namespace xor_cipher
