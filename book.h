#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Book : public Product{
public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string& ISBN, const std::string& author);
    virtual ~Book() override;

    virtual std::set<std::string> keywords() const override;

    virtual std::string displayString() const override;

    virtual void dump(std::ostream& os) const override;

private:
    std::string ISBN_;
    std::string author_;
};
#endif
