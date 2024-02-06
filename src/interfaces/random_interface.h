#ifndef RANDOM_INTERFACE_H
#define RANDOM_INTERFACE_H
#include "../product.h"
#include <map>

class RandomInterface {
public:
    virtual std::string getRandomName() = 0;
    virtual std::string getRandomSurname() = 0;
    virtual Product getRandomProduct(const std::map<Product, int>& products) = 0;
    virtual int getRandomInteger(int min, int max) = 0;

    virtual ~RandomInterface() = 0;
};

#endif