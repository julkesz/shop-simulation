#include "client.h"
#include "random.h"
#include "exceptions/greater_money_substraction_exception.h"

int Client::NUMBER_OF_CLIENTS=0;

Client::Client(std::string nm, std::string snm, Currency mon): Person(nm, snm){
    Random r;
    id=++NUMBER_OF_CLIENTS;
    money=mon;
    numberOfWantedProducts = r.getRandomInteger(1,10);
    basketValue = Currency(0,0);
};

std::string Client::getPosition() const noexcept{
    return "Client";
}

Currency Client::getMoney() const noexcept{
    return money;
}

std::vector<Product> Client::getBasket() const noexcept{
    return basket;
}

void Client::setMoney(Currency mon) noexcept{
    money=mon;
}

void Client::addProduct(Product prod) noexcept{
    basket.push_back(prod);
    basketValue += prod.getPriceGross();
}

unsigned int Client::getNumberOfProducts() const noexcept{
    return basket.size();
}

unsigned int Client::getNumberOfWantedProducts() const noexcept{
    return numberOfWantedProducts;
}

Currency Client::getBasketValue() const noexcept{
    return basketValue;
}

Currency Client::printBill(std::ofstream &outputFile) const noexcept{
    Currency priceOfProducts(0,0);
    int i = 0;
    std::cout << "BILL FOR "<< *this <<std::endl;
    outputFile << "BILL FOR "<< *this <<std::endl;
    for(const auto& p : basket){
        i++;
        priceOfProducts += p.getPriceGross();
        std::cout << i << ". " << p.getName()<<", Price Gross: "<< p.getPriceGross() << std::endl;
        outputFile << i << ". " << p.getName()<<", Price Gross: "<< p.getPriceGross() << std::endl;
    }
    std::cout << "Total price: " << priceOfProducts << std::endl;
    outputFile << "Total price: " << priceOfProducts << std::endl;

    return priceOfProducts;
}

void Client::pay(Currency amount) {
    try {
        money -= amount;
    } catch (GreaterMoneySubstractionException& exc){
        std::cerr << exc.getInfo() << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Client& c)
{
    os << "Client " << c.id << ": " << c.name <<" " << c.surname;
    return os;
}