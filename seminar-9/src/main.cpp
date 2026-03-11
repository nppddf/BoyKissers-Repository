#include <iostream>
#include <string>

#include "../inc/catalog.hpp"

int main()
{
    library::Catalog catalog;

    catalog.addBook(Book("The C Programming Language", 1978));
    catalog.addBook(Book("Modern Operating Systems", 1992));
    catalog.addBook(Book("Algorithms", 1990));
    catalog.addBook(Book("Clean Code", 2008));
    catalog.addBook(Book("Structure and Interpretation of Computer Programs", 1985));
    catalog.addBook(Book("Code", 2000));

    std::cout << "Initial catalog:\n";
    for(const auto& book: catalog.books())
        std::cout << " - " << book << '\n';

    catalog.sortByCatalogOrder();

    std::cout << "\nSorted catalog (year -> title length -> alphabet):\n";
    for(const auto& book: catalog.books())
        std::cout << " - " << book << '\n';

    return 0;
}
