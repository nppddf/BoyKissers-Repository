#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <string>
#include <vector>

#include "../inc/xor_cipher_utils.hpp"

TEST_CASE("XOR cipher encrypts and decrypts with the same key")
{
    const std::string text = "Hello, XOR!";
    const std::string key = "secret";

    std::string encrypted = xor_cipher::encryptText(text, key);
    std::string decrypted = xor_cipher::decryptText(encrypted, key);

    REQUIRE(decrypted == text);
}

TEST_CASE("Binary file is written and read back correctly")
{
    namespace fs = std::filesystem;

    fs::path tempPath = fs::temp_directory_path() / "xor_cipher_test.bin";
    std::vector<uint8_t> data = {0x00, 0x01, 0xFE, 0xFF, 0x42};

    xor_cipher::writeBinaryFile(tempPath.string(), data);
    std::vector<uint8_t> loaded = xor_cipher::readBinaryFile(tempPath.string());

    REQUIRE(loaded == data);

    fs::remove(tempPath);
}
