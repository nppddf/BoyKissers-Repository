#pragma once

#include <cstddef>
#include <iosfwd>

class Book {
public:
    Book();
    Book(const char* title, int year);
    Book(const Book& other);
    Book& operator=(const Book& other);
    Book(Book&& other) noexcept;
    Book& operator=(Book&& other) noexcept;
    ~Book();

    const char* getTitle() const noexcept;
    int getYear() const noexcept;
    std::size_t titleLength() const noexcept;

    void setTitle(const char* newTitle);
    void setYear(int newYear) noexcept;

    void swap(Book& other) noexcept;

private:
    char* title_;
    int year_;
};

bool operator==(const Book& lhs, const Book& rhs);
bool operator!=(const Book& lhs, const Book& rhs);
std::ostream& operator<<(std::ostream& os, const Book& book);
