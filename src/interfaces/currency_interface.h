#ifndef CURRENCY_INTERFACE_H
#define CURRENCY_INTERFACE_H

class CurrencyInterface {
public:
    virtual unsigned int getDollars() const noexcept = 0;
    virtual unsigned int getCents() const noexcept = 0;

    virtual ~CurrencyInterface() = 0;
};

#endif