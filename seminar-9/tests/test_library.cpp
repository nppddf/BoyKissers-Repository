#include <catch2/catch_test_macros.hpp>

#include "../inc/book.hpp"
#include "../inc/catalog.hpp"

#include <string>

TEST_CASE("Book copies own title buffer")
{
    Book original("Original title", 1999);
    Book copy = original;

    REQUIRE(std::string(copy.getTitle()) == "Original title");
    REQUIRE(copy.getTitle() != original.getTitle());

    original.setTitle("Updated");
    REQUIRE(std::string(original.getTitle()) == "Updated");
    REQUIRE(std::string(copy.getTitle()) == "Original title");
}

TEST_CASE("SafeVector copies books independently")
{
    SafeVector<Book> books;
    books.push_back(Book("First", 2000));
    books.push_back(Book("Second", 2001));

    SafeVector<Book> clone = books;
    books[0].setTitle("Changed");

    REQUIRE(clone.size() == 2);
    REQUIRE(std::string(clone[0].getTitle()) == "First");
}

TEST_CASE("SafeVector resize expands and shrinks safely")
{
    SafeVector<Book> books;
    books.push_back(Book("Alpha", 2002));

    books.resize(3);
    REQUIRE(books.size() == 3);
    REQUIRE(std::string(books[1].getTitle()).empty());
    REQUIRE(std::string(books[2].getTitle()).empty());

    books[1].setTitle("Beta");
    books.resize(1);
    REQUIRE(books.size() == 1);
    REQUIRE(std::string(books[0].getTitle()) == "Alpha");
}

TEST_CASE("Catalog sorts according to composite comparator")
{
    library::Catalog catalog;
    catalog.addBook(Book("Z", 2005));             // later year
    catalog.addBook(Book("Beta", 2001));
    catalog.addBook(Book("Alfa", 2001));
    catalog.addBook(Book("Atlas", 2001));         // longer title
    catalog.addBook(Book("Alpha", 1995));
    catalog.addBook(Book("Delta", 2001));

    catalog.sortByCatalogOrder();
    REQUIRE(catalog.size() == 6);

    auto& data = catalog.books();
    REQUIRE(std::string(data[0].getTitle()) == "Alpha");  // earliest year

    // For year 2001: Alfa and Beta have the same length, so alphabet decides.
    REQUIRE(std::string(data[1].getTitle()) == "Alfa");
    REQUIRE(std::string(data[2].getTitle()) == "Beta");
    REQUIRE(std::string(data[3].getTitle()) == "Atlas");
    REQUIRE(std::string(data[4].getTitle()) == "Delta");
    REQUIRE(std::string(data[5].getTitle()) == "Z");
}
