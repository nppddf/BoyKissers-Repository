#pragma once

#include <string>
#include <vector>

std::vector<std::wstring> split_fio(const std::wstring& input);
bool is_valid_fio_characters(const std::wstring& input);
std::wstring to_upper(const std::wstring& input);
std::wstring capitalize_words(const std::wstring& input);
std::wstring format_short_fio(const std::wstring& surname, const std::wstring& name,
                              const std::wstring& patronymic);
