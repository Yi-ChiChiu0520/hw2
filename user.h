#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include "product.h"
/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);
    void viewCart() const;
    bool buyCart();
    void addToCart(Product* product);
    
 

private:
    std::vector<Product*> cart;
    std::string name_;
    double balance_;
    int type_;
};
#endif
