#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace xor_cipher {

std::vector<uint8_t> readBinaryFile(const std::string& path);
void writeBinaryFile(const std::string& path, const std::vector<uint8_t>& data);
std::string encryptText(const std::string& text, const std::string& key);
std::string decryptText(const std::string& text, const std::string& key);

}  // namespace xor_cipher
