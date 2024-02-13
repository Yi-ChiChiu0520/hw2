#include <sstream>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string& genre, const std::string& rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating){
}


Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {
  std::set<std::string> keywordSet;

  keywordSet.insert(convToLower(genre_));
  // Extract keywords from the name
  std::set<std::string> nameKeywords = parseStringToWords(convToLower(name_));
  keywordSet.insert(nameKeywords.begin(), nameKeywords.end());
  
  return keywordSet;
}


std::string Movie::displayString() const {
    std::ostringstream oss;
   oss << name_ << "\n" <<"Genre: "<<genre_<< " " << "Rating: " << rating_ << "\n" << price_ << " "<< qty_ << " left.";
    return oss.str();
}

void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}

