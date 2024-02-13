#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string& ISBN, const std::string& author)
    : Product(category, name, price, qty), ISBN_(ISBN), author_(author) {

  

}

Book::~Book() {}

std::set<std::string> Book::keywords() const {
  std::set<std::string> keywordSet;
  
  keywordSet.insert(ISBN_);

  // Extract keywords from the name
  std::set<std::string> nameKeywords = parseStringToWords(convToLower(name_));
  keywordSet.insert(nameKeywords.begin(), nameKeywords.end());

  // Extract keywords from the author
  std::set<std::string> authorKeywords = parseStringToWords(convToLower(author_));
  keywordSet.insert(authorKeywords.begin(), authorKeywords.end());
  
  return keywordSet;
}


std::string Book::displayString() const {
    std::ostringstream oss;
    oss << name_ << "\n" << "Author: " << author_ << " " << "ISBN: " << ISBN_ << "\n" << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << std::endl;
}

