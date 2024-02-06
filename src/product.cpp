#include "product.h" 

int Product::NUMBER_OF_PRODUCTS=0;

void Product::updatePriceGross(Currency priNet, TaxCategory taxCat) noexcept{
    priceGross = priNet + priNet * ( taxCat / 100.0 );
}
    
Product::Product(std::string nm, Currency priNet, TaxCategory taxCat):id(++NUMBER_OF_PRODUCTS), name(nm), priceNet(priNet), tax(taxCat){
    updatePriceGross(priNet, taxCat);
}

const int Product::getId() const noexcept{
    return id;
}

std::string Product::getName() const noexcept{
    return name;
}

Currency Product::getPriceNet() const noexcept{
    return priceNet;
}

Currency Product::getPriceGross() const noexcept{
    return priceGross;
}

Product::TaxCategory Product::getTaxCategory() const noexcept{
    return tax;
}

void Product::setName(std::string nm) noexcept{
    name=nm;
}

void Product::setPriceNet(Currency priNet) noexcept{
    priceNet=priNet;
    updatePriceGross(priceNet, tax);
}

void Product::setTaxCategory(TaxCategory tx) noexcept{
    tax=tx;
    updatePriceGross(priceNet, tax);
}

bool Product::operator<(const Product& prod) const {
    return name < prod.name;
}

bool Product::operator>(const Product& prod) const { 
    return *this > prod; 
}

bool Product::operator<=(const Product& prod) const { 
    return !(*this > prod); 
}

bool Product::operator>=(const Product& prod) const { 
    return !(*this < prod); 
}

bool Product::operator==(const Product& prod) const {
    return name == prod.name;
}

bool Product::operator!=(const Product& prod) const {
    return !(*this == prod);
}

std::ostream& operator<<(std::ostream& os, const Product& prod)
{
    os << "Product "<< prod.id << ": Name: " << prod.name <<", Price Net: " << prod.priceNet << ", Price Gross: "<< prod.priceGross << ", Tax Percentage: "<< prod.tax;
    return os;
}