#include <sstream>
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string& genre, const std::string& rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating){}

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> kw;
    // Assuming you have fields like genre_ (and potentially director_ or similar)
    std::istringstream iss(genre_); // Splitting genre into keywords might not make sense, adjust as needed
    std::string word;
    while (iss >> word) {
        kw.insert(word);
    }
    // If you have other fields like director's name that should contribute to keywords, process them similarly
    // Example for a director (commented out if not applicable):
    // std::istringstream directorStream(director_);
    // while (directorStream >> word) {
    //     kw.insert(word);
    // }
    return kw;
}


std::string Movie::displayString() const {
    std::ostringstream oss;
   oss << name_ << "\n" <<"Genre: "<<genre_<< " " << "Rating: " << rating_ << "\n" << price_ << " "<< qty_ << " left.";
    return oss.str();
}

void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}

