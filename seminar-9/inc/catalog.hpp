#pragma once

#include <cstddef>

#include "book.hpp"
#include "safe_vector.hpp"

namespace library {

struct BookCatalogComparator {
    bool operator()(const Book& lhs, const Book& rhs) const;
};

class Catalog {
public:
    void addBook(const Book& book);
    void addBook(Book&& book);

    std::size_t size() const noexcept;

    SafeVector<Book>& books() noexcept;
    const SafeVector<Book>& books() const noexcept;

    void sortByCatalogOrder();

private:
    SafeVector<Book> books_;
};

}  // namespace library
