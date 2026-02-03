#include <iostream>
#include <locale>
#include <string>

#include "../inc/name_utils.h"

int main()
{
    std::wcout << L"Введите ваше полное ФИО (Фамилия Имя Отчество): " << std::endl;
    std::wstring input;
    std::getline(std::wcin, input);
    if (!is_valid_fio_characters(input))
    {
        std::wcout << L"Ошибка: ФИО должно содержать только буквы, пробелы." << std::endl;
        std::wcout << L"Введите ФИО заново" << std::endl;
        return 1;
    }

    try
    {
        auto parts                     = split_fio(input);
        const std::wstring& surname    = parts[0];
        const std::wstring& name       = parts[1];
        const std::wstring& patronymic = parts[2];
        
        std::wstring upper_all         = to_upper(surname + L" " + name + L" " + patronymic);
        std::wstring capitalized       = capitalize_words(surname + L" " + name + L" " + patronymic);
        std::wstring short_form        = format_short_fio(surname, name, patronymic);

        std::wcout << L"\nВарианты записи вашего ФИО:" << std::endl;
        std::wcout << upper_all << std::endl;
        std::wcout << capitalized << std::endl;
        std::wcout << short_form << std::endl;
    }
    catch (const std::exception&)
    {
        std::wcout << L"Ошибка: некорректный формат ФИО. Нужно ввести три слова: фамилию, имя и отчество."
                   << std::endl;
        return 1;
    }

    return 0;
}
