#ifndef CLIENT_H
#define CLIENT_H
#include "person.h"
#include "product.h"
#include <vector>
#include <fstream>
#include <iostream>

class Client: public Person{
public:
    Client(std::string nm, std::string snm, Currency mon = Currency(0,0));
    std::string getPosition() const noexcept override;

    Currency getMoney() const noexcept;
    void setMoney(Currency mon) noexcept;
    std::vector<Product> getBasket() const noexcept;
    unsigned int getNumberOfProducts() const noexcept;
    unsigned int getNumberOfWantedProducts() const noexcept;
    Currency getBasketValue() const noexcept;
    void pay(Currency amount);
    
    virtual void addProduct(Product prod) noexcept;
    virtual Currency printBill(std::ofstream &outputFile) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Client& c);

protected:
    static int NUMBER_OF_CLIENTS;
    Currency money;
    unsigned int numberOfWantedProducts;
    std::vector<Product> basket;
    Currency basketValue;
};

#endif