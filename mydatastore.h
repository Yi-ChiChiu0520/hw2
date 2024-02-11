#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "product.h"
#include "user.h"
#include <vector>
#include <set>
#include <map>
#include <string>


class MyDataStore: public DataStore {
public:
    ~MyDataStore() override;
    /**
     * Adds a product to the data store
     */
    virtual void addProduct(Product* p) override;

    /**
     * Adds a user to the data store
     */
    virtual void addUser(User* u) override;

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    /**
     * Reproduce the database file from the current Products and User values
     */
    virtual void dump(std::ostream& ofile) override;
    void addProductToUserCart(const std::string& username, Product* product);
    void viewUserCart(const std::string& username);
    void buyUserCart(const std::string& username);
    
private: 
    // Containers for managing products and users
    std::vector<Product*> products;
    std::vector<User*> users;

    // Maps each keyword to a set of products that contain that keyword
    std::map<std::string, std::set<Product*>> keywordToProducts;
};

#endif
