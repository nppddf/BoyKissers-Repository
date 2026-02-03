#include <iostream>
#include <locale>
#include <string>

#include "../inc/name_utils.h"

int main()
{
    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale());
    std::wcout.imbue(std::locale());

    std::wcout << L"Введите ваше полное ФИО (Фамилия Имя Отчество): " << std::endl;
    std::wstring input;
    std::getline(std::wcin, input);
    if (!name_utils::isValidFioCharacters(input))
    {
        std::wcout << L"Ошибка: ФИО должно содержать только буквы, пробелы." << std::endl;
        std::wcout << L"Введите ФИО заново" << std::endl;
        return 1;
    }

    try
    {
        auto parts                     = name_utils::splitFio(input);
        const std::wstring& surname    = parts[0];
        const std::wstring& name       = parts[1];
        const std::wstring& patronymic = parts[2];

        std::wstring upperAll    = name_utils::toUpper(surname + L" " + name + L" " + patronymic);
        std::wstring capitalized = name_utils::capitalizeWords(surname + L" " + name + L" " + patronymic);
        std::wstring shortForm   = name_utils::formatShortFio(surname, name, patronymic);

        std::wcout << L"\nВарианты записи вашего ФИО:" << std::endl;
        std::wcout << upperAll << std::endl;
        std::wcout << capitalized << std::endl;
        std::wcout << shortForm << std::endl;
    }
    catch (const std::exception&)
    {
        std::wcout << L"Ошибка: некорректный формат ФИО. Нужно ввести три слова: фамилию, имя и отчество."
                   << std::endl;
        return 1;
    }

    return 0;
}
