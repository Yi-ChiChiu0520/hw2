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
    products.insert(p);

    // Use parseStringToWords to process product name and/or description for keywords
    std::set<std::string> keywords = p->keywords();

    for (std::string keyword: keywords) {
      if (keywordToProducts.find(keyword) == keywordToProducts.end()) {
        keywordToProducts[keyword] = std::set<Product*>();
      }
      keywordToProducts[keyword].insert(p);
    }   
}

/**     
* * Adds a user to the data store
*/
void MyDataStore::addUser(User* u){
    users.insert(u);

    userMap[u->getName()] = u;
}

/**
* Performs a search of products whose keywords match the given "terms"
*  type 0 = AND search (intersection of results for each term) while
*  type 1 = OR search (union of results for each term)
*/
std::vector<Product*> MyDataStore:: search(std::vector<std::string>& terms, int type){
    std::vector<Product*> results;
    if(terms.empty()) return results;

    std::set<Product*> searchResults;
    std::string term = terms.back();
    terms.pop_back();
    if (keywordToProducts.find(term) == keywordToProducts.end()) {
      searchResults = std::set<Product *>();
    } else{ 
      searchResults = keywordToProducts[term];
    }

    for (std::string currentTerm: terms) {
      std::set<Product *> currentTermResults;
      if (keywordToProducts.find(currentTerm) == keywordToProducts.end()) {
        currentTermResults = std::set<Product *>();
      } else{ 
        currentTermResults = keywordToProducts[currentTerm];
      }

      if (type == 0) {
        searchResults = setIntersection(searchResults,currentTermResults);
      } else {
        searchResults = setUnion(searchResults,currentTermResults);
      }
    }

    return std::vector<Product *>(searchResults.begin(),searchResults.end());
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
    if (userMap.find(username) == userMap.end()) {
      std::cout << "Invalid request" << std::endl;
      return;
    }

    User *user = userMap[username];
    if (userCart.find(user) == userCart.end()) {
      userCart[user] = std::vector<Product*>();
    }
    
    userCart[user].push_back(product);
}

void MyDataStore::viewUserCart(const std::string& username) {
    std::map<std::string, User*>::iterator it = userMap.find(username);
    int count=0; 
    if (it == userMap.end()) {
      std::cout << "Invalid username" << std::endl;
      return; 
    }
        User* user = it->second;
        std::map<User *, std::vector<Product *>>::iterator cartIt = userCart.find(user);
        if (cartIt != userCart.end()) {
            for (std::vector<Product*>::iterator prodIt = cartIt->second.begin(); prodIt != cartIt->second.end(); ++prodIt) {
                ++count; 
                cout<<"Item "<<count<<endl;
                std::cout << (*prodIt)->displayString() << std::endl;
            }
        } else {
            std::cout << "The cart is empty." << std::endl;
        }
}


void MyDataStore::buyUserCart(const std::string& username) {
    std::map<std::string, User*>::iterator userIt = userMap.find(convToLower(username)); // Explicit iterator type
    if (userIt == userMap.end()) {
      std::cout << "Invalid username" << std::endl;
      return;
    }
        User* user = userIt->second;
        std::vector<Product*>& cart = userCart[user]; // Direct reference to avoid unnecessary lookups

        for (std::vector<Product*>::iterator it = cart.begin(); it != cart.end();) {
            Product* product = *it;
            if (product->getQty() > 0 && user->getBalance() >= product->getPrice()) {
                user->deductAmount(product->getPrice());
                product->subtractQty(1);
                it = cart.erase(it); // Remove product after purchase
            } else {
                ++it; // Skip this product if not purchasable
            }
        }
} 
