#ifndef CURRENCY_H
#define CURRENCY_H
#include "interfaces/currency_interface.h"
#include <iostream>

class Currency: public CurrencyInterface
{
public:
    Currency(unsigned int dlr=0, unsigned int cnt=0);
    unsigned int getDollars() const noexcept override;
    unsigned int getCents() const noexcept override;

    Currency& operator+=(const Currency& curr);
    Currency& operator-=(const Currency& curr);
    Currency& operator*=(const double& multiplier);

    Currency operator+(const Currency& curr) const;
    Currency operator-(const Currency& curr) const;
    Currency operator*(const double& multiplier) const;

    bool operator<(const Currency& curr) const;
    bool operator> (const Currency& curr) const;
    bool operator<=(const Currency& curr) const;
    bool operator>=(const Currency& curr) const;
    bool operator==(const Currency& curr) const;

    friend std::ostream& operator<<(std::ostream& os, const Currency& curr);

private:
    unsigned int dollars;
    unsigned int cents;
};

#endif



