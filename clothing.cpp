#include <sstream>
#include "clothing.h"
#include "util.h"


using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string& brand, const std::string& size)
    : Product(category, name, price, qty), brand_(brand), size_(size){
    
    
    }

Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const {
  std::set<std::string> keywordSet;
    // Extract keywords from the brand
    std::set<std::string> brandKeywords = parseStringToWords(convToLower(brand_));
    keywordSet.insert(brandKeywords.begin(), brandKeywords.end());

    // Optionally add the size as a keyword if it's relevant
    std::set<std::string> nameKeywords = parseStringToWords(convToLower(name_));
    keywordSet.insert(nameKeywords.begin(), nameKeywords.end());
    
    return keywordSet;
}


std::string Clothing::displayString() const {
    std::ostringstream oss;
    oss <<name_ << "\n" <<"Size: "<<size_<< " " << "Brand: " << brand_ << "\n" << price_ << " "<< qty_ << " left.";
    return oss.str();
}

void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}

