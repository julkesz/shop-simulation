#ifndef RANDOM_H
#define RANDOM_H
#include "interfaces/random_interface.h"

class Random : public RandomInterface{
public:
    std::string getRandomName() override;
    std::string getRandomSurname() override;
    Product getRandomProduct(const std::map<Product, int>& products) override;
    int getRandomInteger(int min, int max) override;
};

#endif