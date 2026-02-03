#pragma once

#include <string>
#include <vector>

namespace name_utils
{

std::vector<std::wstring> splitFio(const std::wstring& input);
bool isValidFioCharacters(const std::wstring& input);
std::wstring toUpper(const std::wstring& input);
std::wstring capitalizeWords(const std::wstring& input);
std::wstring formatShortFio(const std::wstring& surname, const std::wstring& name,
                            const std::wstring& patronymic);

}  // namespace name_utils
