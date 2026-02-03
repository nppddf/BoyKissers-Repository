#include "../inc/name_utils.h"

#include <algorithm>
#include <cctype>
#include <cwctype>
#include <locale>
#include <sstream>
#include <stdexcept>

bool is_letter(wchar_t ch)
{
    return std::iswalpha(ch) != 0;
}

bool is_valid_fio_characters(const std::wstring& input)
{
    for (wchar_t ch : input)
    {
        if (ch == L' ')
            continue;
        if (!is_letter(ch))
            return false;
    }
    return true;
}

std::vector<std::wstring> split_fio(const std::wstring& input)
{
    std::wstringstream wss(input);
    std::wstring part;
    std::vector<std::wstring> parts;
    while (wss >> part)
    {
        parts.push_back(part);
    }
    if (parts.size() != 3)
    {
        throw std::runtime_error("Expected three words: surname, name, patronymic.");
    }
    return parts;
}

std::wstring to_upper(const std::wstring& input)
{
    std::wstring result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](wchar_t ch) { return std::towupper(ch); });
    return result;
}

std::wstring word_capitalize(const std::wstring& word)
{
    if (word.empty())
    {
        return word;
    }
    std::wstring result = word;
    result[0]           = std::towupper(result[0]);
    for (std::size_t i = 1; i < result.size(); ++i)
    {
        result[i] = std::towlower(result[i]);
    }
    return result;
}

std::wstring capitalize_words(const std::wstring& input)
{
    std::wstringstream wss(input);
    std::wstring word;
    std::wstring result;
    bool first = true;
    while (wss >> word)
    {
        if (!first)
        {
            result += L' ';
        }
        first = false;
        result += word_capitalize(word);
    }
    return result;
}

std::wstring format_short_fio(const std::wstring& surname, const std::wstring& name,
                              const std::wstring& patronymic)
{
    std::wstring formatted_surname = word_capitalize(surname);
    wchar_t name_initial           = name.empty() ? L'\0' : std::towupper(name[0]);
    wchar_t patronymic_initial     = patronymic.empty() ? L'\0' : std::towupper(patronymic[0]);
    std::wstring result            = formatted_surname;
    result += L' ';
    if (name_initial != L'\0')
    {
        result += name_initial;
        result += L'.';
        result += L' ';
    }
    if (patronymic_initial != L'\0')
    {
        result += patronymic_initial;
        result += L'.';
    }
    return result;
}
