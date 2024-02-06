#ifndef PRODUCT_INTERFACE_H
#define PRODUCT_INTERFACE_H
#include "../currency.h"
#include <string>


class ProductInterface {
public:
    enum TaxCategory { low = 0, medium = 8, high = 23 };
    virtual const int getId() const noexcept = 0;
    virtual std::string getName() const noexcept = 0;
    virtual Currency getPriceNet() const noexcept = 0;
    virtual Currency getPriceGross() const noexcept = 0;
    virtual TaxCategory getTaxCategory() const noexcept = 0;

    virtual void setName(std::string nm) noexcept = 0;
    virtual void setPriceNet(Currency priNet) noexcept = 0;
    virtual void setTaxCategory(TaxCategory tx) noexcept = 0;

    virtual ~ProductInterface() = 0;
};

#endif