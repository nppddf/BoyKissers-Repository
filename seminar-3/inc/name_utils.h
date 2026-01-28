#pragma once

#include <string>
#include <vector>

// Устанавливает русскую локаль для корректной работы с кириллицей.
void setup_russian_locale();

// Разбивает исходную строку ФИО на три части: фамилия, имя, отчество.
// Бросает std::runtime_error, если формат некорректный.
std::vector<std::wstring> split_fio(const std::wstring& input);

// Проверяет, что строка ФИО содержит только буквы, пробелы и дефисы.
// Возвращает false, если встречены другие символы.
bool is_valid_fio_characters(const std::wstring& input);

// Переводит все буквы строки в верхний регистр.
std::wstring to_upper(const std::wstring& input);

// Каждое слово: первая буква большая, остальные маленькие.
std::wstring capitalize_words(const std::wstring& input);

// Формирует строку вида "Фамилия И. О."
std::wstring format_short_fio(const std::wstring& surname,
                              const std::wstring& name,
                              const std::wstring& patronymic);

