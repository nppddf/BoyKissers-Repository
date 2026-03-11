#include "../inc/catalog.hpp"

#include <algorithm>
#include <string>
#include <tuple>
#include <utility>

namespace library {

bool BookCatalogComparator::operator()(
    const Book& lhs, const Book& rhs) const
{
    auto lhsKey = std::make_tuple(
        lhs.getYear(), lhs.titleLength(), std::string(lhs.getTitle()));
    auto rhsKey = std::make_tuple(
        rhs.getYear(), rhs.titleLength(), std::string(rhs.getTitle()));
    return lhsKey < rhsKey;
}

void Catalog::addBook(const Book& book)
{
    books_.push_back(book);
}

void Catalog::addBook(Book&& book)
{
    books_.push_back(std::move(book));
}

std::size_t Catalog::size() const noexcept
{
    return books_.size();
}

SafeVector<Book>& Catalog::books() noexcept
{
    return books_;
}

const SafeVector<Book>& Catalog::books() const noexcept
{
    return books_;
}

void Catalog::sortByCatalogOrder()
{
    if(books_.size() < 2)
        return;

    std::sort(books_.begin(), books_.end(), BookCatalogComparator{});
}

}  // namespace library
