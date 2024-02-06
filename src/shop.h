#ifndef SHOP_H
#define SHOP_H
#include "interfaces/shop_interface.h"

class Shop: public ShopInterface{
public:
    void startSimulation(unsigned int iterationNumber, std::ofstream &outputFile) override;

    void addEmployee(std::string name, std::string surname) override;
    void addProduct(std::string name, unsigned int dollars, unsigned int cents, int taxCat, int amount=0) override;
    void enterClient(std::string name, std::string surname, unsigned int dollars, unsigned int cents, int type) override;
    void addCounter(unsigned int dollars, unsigned int cents) noexcept override;

    void removeEmployee(std::string name, std::string surname) override;
    void leaveClient(std::string name, std::string surname) override;
    
    void removeProduct(std::string name) override;
    void setProductAmount(std::string name, int amount) override;
    void increaseProductAmount(std::string name) override;
    void decreaseProductAmount(std::string name) override;

    unsigned int getNumberOfUnassignedEmployees() const noexcept override;
    unsigned int getNumberOfDeactivatedCounters() const noexcept override;
    unsigned int getNumberOfActivatedCounters() const noexcept override;
    unsigned int getNumberOfClients() const noexcept override;
    unsigned int getNumberOfProducts() const noexcept override;

    void generateEmployees(int numberOfEmployees, std::ofstream &outputFile) override;
    void assignEmployeesToCounters(int numberOfEmployees, std::ofstream &outputFile) override;
    void chooseCounterByClient(std::vector<std::unique_ptr<Client>>::iterator iter) override;

    void printAllInfo(std::ofstream &outputFile) const override;
    void printUnassignedEmployees(std::ofstream &outputFile) const override;
    void printDeactivatedCounters(std::ofstream &outputFile) const override;
    void printActivatedCounters(std::ofstream &outputFile) const override;
    void printClients(std::ofstream &outputFile) const override;
    void printProducts(std::ofstream &outputFile) const override;

private:
    std::vector<std::unique_ptr<Employee>> unassignedEmployees;
    std::vector<std::unique_ptr<Counter>> deactivatedCounters;
    std::vector<std::unique_ptr<Counter>> activatedCounters;
    std::vector<std::unique_ptr<Client>> clients;
    std::map<Product, int> products;

};

#endif
