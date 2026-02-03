#include "../inc/name_utils.h"

#include <algorithm>
#include <cwctype>
#include <sstream>
#include <stdexcept>

namespace name_utils
{
namespace
{

bool isLetter(wchar_t character)
{
    return std::iswalpha(character) != 0;
}

std::wstring capitalizeWord(const std::wstring& word)
{
    if (word.empty())
    {
        return word;
    }

    std::wstring result = word;
    result[0]           = static_cast<wchar_t>(std::towupper(result[0]));
    for (std::size_t i = 1; i < result.size(); ++i)
    {
        result[i] = static_cast<wchar_t>(std::towlower(result[i]));
    }
    return result;
}

}  // namespace

bool isValidFioCharacters(const std::wstring& input)
{
    return std::all_of(input.begin(), input.end(),
                       [](wchar_t character) { return (character == L' ') || isLetter(character); });
}

std::vector<std::wstring> splitFio(const std::wstring& input)
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

std::wstring toUpper(const std::wstring& input)
{
    std::wstring result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](wchar_t character) { return static_cast<wchar_t>(std::towupper(character)); });
    return result;
}

std::wstring capitalizeWords(const std::wstring& input)
{
    std::wstringstream wss(input);
    std::wstring word;
    std::wstring result;

    bool firstWord = true;
    while (wss >> word)
    {
        if (!firstWord)
        {
            result += L' ';
        }
        firstWord = false;
        result += capitalizeWord(word);
    }

    return result;
}

std::wstring formatShortFio(const std::wstring& surname, const std::wstring& name,
                            const std::wstring& patronymic)
{
    std::wstring formattedSurname = capitalizeWord(surname);
    wchar_t nameInitial =
            name.empty() ? L'\0' : static_cast<wchar_t>(std::towupper(static_cast<wchar_t>(name[0])));
    wchar_t patronymicInitial =
            patronymic.empty() ? L'\0'
                               : static_cast<wchar_t>(std::towupper(static_cast<wchar_t>(patronymic[0])));

    std::wstring result = formattedSurname;
    result += L' ';
    if (nameInitial != L'\0')
    {
        result += nameInitial;
        result += L'.';
        result += L' ';
    }
    if (patronymicInitial != L'\0')
    {
        result += patronymicInitial;
        result += L'.';
    }
    return result;
}

}  // namespace name_utils
