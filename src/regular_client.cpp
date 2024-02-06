#include "regular_client.h"

RegularClient::RegularClient(std::string nm, std::string snm, Currency mon, double disc): Client(nm, snm, mon){
    discount = disc;
};

void RegularClient::addProduct(Product prod) noexcept{
    basket.push_back(prod);
    basketValue += prod.getPriceGross() * ( (100 - discount) / 100.0 );
}

Currency RegularClient::printBill(std::ofstream &outputFile) const noexcept{
    Currency priceOfProducts(0,0);
    Currency discountedPriceOfProducts(0,0);
    int i = 0;
    std::cout << "BILL FOR "<< *this <<std::endl;
    outputFile << "BILL FOR "<< *this <<std::endl;
    for(const auto& p : basket){
        i++;
        priceOfProducts += p.getPriceGross();
        std::cout << i << ". " << p.getName()<<", Price Gross: "<< p.getPriceGross() << std::endl;
        outputFile << i << ". " << p.getName()<<", Price Gross: "<< p.getPriceGross() << std::endl;
    }
    discountedPriceOfProducts = priceOfProducts * ( (100 - discount) / 100.0 );
    std::cout << "Discount for regular clients: " << discount << "%: " << priceOfProducts - discountedPriceOfProducts << std::endl;
    std::cout << "Total price: " << discountedPriceOfProducts << std::endl;
    outputFile << "Discount for regular clients: " << discount << "%: " << priceOfProducts - discountedPriceOfProducts << std::endl;
    outputFile << "Total price: " << discountedPriceOfProducts << std::endl;

    return discountedPriceOfProducts;
}