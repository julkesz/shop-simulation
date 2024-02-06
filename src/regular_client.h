#ifndef REGULAR_CLIENT_H
#define REGULAR_CLIENT_H
#include "client.h"

class RegularClient: public Client{
public:
    RegularClient(std::string nm, std::string snm, Currency mon = Currency(0,0), double dics = 20.0);

    void addProduct(Product prod) noexcept override;
    Currency printBill(std::ofstream &outputFile) const noexcept override;

private:
    double discount;
};

#endif