#include <sstream>
#include <algorithm> // For std::find_if
#include <vector>
#include <iostream>
#include "mydatastore.h"
#include "util.h"
#include <vector>
#include <set>
#include <map>
#include <string>

using namespace std;

MyDataStore::~MyDataStore() {
    // clean up vector products
    for(Product* p: products) {
        delete p;
    }
    // clean up vector users
    for(User* u: users) {
        delete u;
    }
}

/**
* Adds a product to the data store
*/
void MyDataStore::addProduct(Product* p){
    // add product to vector product
    products.push_back(p); 

    // Use parseStringToWords to process product name and/or description for keywords
    std::set<std::string> nameKeywords = parseStringToWords(p->getName());
    // If applicable, extend to other fields like description
    // std::set<std::string> descriptionKeywords = parseStringToWords(p->getDescription());
    
    // Combine keywords from all relevant fields (for now, just the name)
    std::set<std::string> combinedKeywords = nameKeywords;
    // If applicable, merge description keywords
    // combinedKeywords.insert(descriptionKeywords.begin(), descriptionKeywords.end());

    // Insert product into keyword map
    for(std::set<std::string>::iterator k = combinedKeywords.begin(); k != combinedKeywords.end(); ++k) {
        keywordToProducts[*k].insert(p);
    }
}

/**     
* * Adds a user to the data store
*/
void MyDataStore::addUser(User* u){
    users.push_back(u);
}

/**
* Performs a search of products whose keywords match the given "terms"
*  type 0 = AND search (intersection of results for each term) while
*  type 1 = OR search (union of results for each term)
*/
std::vector<Product*> MyDataStore:: search(std::vector<std::string>& terms, int type){
std::vector<Product*> results;
    std::set<Product*> searchResults;
    if(terms.empty()) return results;

    for(std::vector<std::string>::iterator term = terms.begin(); term != terms.end(); ++term) {
        *term = convToLower(*term);
    }

    // Initialize searchResults appropriately based on the search type
    if(type == 0 && !terms.empty()) { // AND search initialization
        searchResults = keywordToProducts[terms[0]];
    }
    // Perform the search
    for(size_t i = (type == 0 ? 1 : 0); i < terms.size(); ++i) {
        if(keywordToProducts.find(terms[i]) != keywordToProducts.end()) {
            if(type == 0) { // AND search
                searchResults = setIntersection(searchResults, keywordToProducts[terms[i]]);
            } else { // OR search
                searchResults = setUnion(searchResults, keywordToProducts[terms[i]]);
            }
        } else if (type == 0) { // If AND search and term not found, clear results
            searchResults.clear();
            break;
        }
    }

    for(std::set<Product*>::iterator p = searchResults.begin(); p != searchResults.end(); ++p) {
        results.push_back(*p);
    }
    return results;
}

/**
 * * Reproduce the database file from the current Products and User values
*/
void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>" << std::endl;
    for(Product* p : products) {
        p->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    
    ofile << "<users>" << std::endl;
    for(User* u : users) {
        u->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void MyDataStore::addProductToUserCart(const std::string& username, Product* product) {
    std::string userKey = convToLower(username);
    auto it = std::find_if(users.begin(), users.end(), [&userKey](const User* user) {
        return convToLower(user->getName()) == userKey;
    });
    if (it != users.end()) {
        (*it)->addToCart(product);
    } else {
        std::cerr << "Invalid username" << std::endl;
    }
}

void MyDataStore::viewUserCart(const std::string& username) {
    std::string userKey = convToLower(username);
    auto it = std::find_if(users.begin(), users.end(), [&userKey](const User* user) {
        return convToLower(user->getName()) == userKey;
    });
    if (it != users.end()) {
        (*it)->viewCart();
    } else {
        std::cerr << "Invalid username" << std::endl;
    }
}

void MyDataStore::buyUserCart(const std::string& username) {
    std::string userKey = convToLower(username);
    auto it = std::find_if(users.begin(), users.end(), [&userKey](const User* user) {
        return convToLower(user->getName()) == userKey;
    });
    if (it != users.end()) {
        (*it)->buyCart();
    } else {
        std::cerr << "Invalid username" << std::endl;
    }
}