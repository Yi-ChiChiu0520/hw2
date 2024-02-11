#include <sstream>
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string& brand, const std::string& size)
    : Product(category, name, price, qty), brand_(brand), size_(size){}

Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> kw;
    std::istringstream iss(brand_); // Assuming brand_ is a relevant field
    std::string word;
    while (iss >> word) {
        kw.insert(word);
    }
    // Optionally, if size is relevant for keywords, though it usually isn't for clothing
    kw.insert(size_);
    return kw;
}


std::string Clothing::displayString() const {
    std::ostringstream oss;
    oss <<name_ << "\n" <<"Size: "<<size_<< " " << "Brand: " << brand_ << "\n" << price_ << " "<< qty_ << " left.";
    return oss.str();
}

void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << brand_ << "\n" << size_ << std::endl;
}

