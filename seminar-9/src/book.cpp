#include "../inc/book.hpp"

#include <cstring>
#include <ostream>
#include <utility>

namespace {

char* duplicateTitle(const char* source)
{
    if(source == nullptr)
        source = "";

    std::size_t length = std::strlen(source);
    char* buffer = new char[length + 1];
    std::memcpy(buffer, source, length + 1);
    return buffer;
}

}  // namespace

Book::Book()
    : title_(duplicateTitle("")), year_(0)
{
}

Book::Book(const char* title, int year)
    : title_(duplicateTitle(title)), year_(year)
{
}

Book::Book(const Book& other)
    : title_(duplicateTitle(other.getTitle())), year_(other.year_)
{
}

Book& Book::operator=(const Book& other)
{
    if(this == &other)
        return *this;

    char* newTitle = duplicateTitle(other.getTitle());
    delete[] title_;
    title_ = newTitle;
    year_ = other.year_;
    return *this;
}

Book::Book(Book&& other) noexcept
    : title_(other.title_), year_(other.year_)
{
    other.title_ = nullptr;
    other.year_ = 0;
}

Book& Book::operator=(Book&& other) noexcept
{
    if(this == &other)
        return *this;

    delete[] title_;
    title_ = other.title_;
    year_ = other.year_;
    other.title_ = nullptr;
    other.year_ = 0;
    return *this;
}

Book::~Book()
{
    delete[] title_;
}

const char* Book::getTitle() const noexcept
{
    static const char emptyTitle[] = "";
    return title_ ? title_ : emptyTitle;
}

int Book::getYear() const noexcept
{
    return year_;
}

std::size_t Book::titleLength() const noexcept
{
    return title_ ? std::strlen(title_) : 0U;
}

void Book::setTitle(const char* newTitle)
{
    char* updated = duplicateTitle(newTitle);
    delete[] title_;
    title_ = updated;
}

void Book::setYear(int newYear) noexcept
{
    year_ = newYear;
}

void Book::swap(Book& other) noexcept
{
    std::swap(title_, other.title_);
    std::swap(year_, other.year_);
}

bool operator==(const Book& lhs, const Book& rhs)
{
    return lhs.getYear() == rhs.getYear() &&
           std::strcmp(lhs.getTitle(), rhs.getTitle()) == 0;
}

bool operator!=(const Book& lhs, const Book& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Book& book)
{
    os << '"' << book.getTitle() << "\" (" << book.getYear() << ')';
    return os;
}
