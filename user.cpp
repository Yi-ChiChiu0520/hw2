#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type) :
    name_(name), balance_(balance), type_(type)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << endl;
}

// In User.cpp
void User::addToCart(Product* product) {
    cart.push_back(product);
}

void User::viewCart() const {
    for(std::vector<Product*>::const_iterator it = cart.begin(); it != cart.end(); ++it) {
        Product* product = *it;
        std::cout << product->displayString() << std::endl;
    }
}

bool User::buyCart() {
    // Implement purchasing logic...
    for(std::vector<Product*>::iterator it = cart.begin(); it != cart.end(); ) {
        Product* product = *it;
        if(product->getQty() > 0 && balance_ >= product->getPrice()) {
            balance_ -= product->getPrice();
            product->subtractQty(1);
            it = cart.erase(it); // Correctly remove the product from the cart after purchase
        } else {
            ++it;
        }
    }
    return true;
}