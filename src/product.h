#ifndef PRODUCT_H
#define PRODUCT_H
#include "interfaces/product_interface.h"


class Product : public ProductInterface {
public:
    Product(std::string nm, Currency priNet = Currency(0,0), TaxCategory taxCat = low);

    const int getId() const noexcept override;
    std::string getName() const noexcept override;
    Currency getPriceNet() const noexcept override;
    Currency getPriceGross() const noexcept override;
    TaxCategory getTaxCategory() const noexcept override;

    void setName(std::string nm) noexcept override;
    void setPriceNet(Currency priNet) noexcept override;
    void setTaxCategory(TaxCategory tx) noexcept override;

    bool operator<(const Product& prod) const;
    bool operator>(const Product& prod) const;
    bool operator<=(const Product& prod) const;
    bool operator>=(const Product& prod) const;

    bool operator==(const Product& prod) const;
    bool operator!=(const Product& prod) const;

    friend std::ostream& operator<<(std::ostream& os, const Product& prod);

private:
    static int NUMBER_OF_PRODUCTS;
    const int id;
    std::string name;
    Currency priceNet;
    Currency priceGross;
    TaxCategory tax;

    void updatePriceGross(Currency priNet, TaxCategory taxCat) noexcept;
};

#endif