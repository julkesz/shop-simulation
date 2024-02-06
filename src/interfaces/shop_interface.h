#ifndef SHOP_INTERFACE_H
#define SHOP_INTERFACE_H

#include "../counter.h"
#include "../product.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

class ShopInterface {
public:
    virtual void startSimulation(unsigned int iterationNumber, std::ofstream &outputFile) = 0;

    virtual void addEmployee(std::string name, std::string surname) = 0;
    virtual void addProduct(std::string name, unsigned int dollars, unsigned int cents, int taxCat, int amount = 0) = 0;
    virtual void enterClient(std::string name, std::string surname, unsigned int dollars, unsigned int cents, int type) = 0;
    virtual void addCounter(unsigned int dollars, unsigned int cents) noexcept = 0;

    virtual void removeEmployee(std::string name, std::string surname) = 0;
    virtual void leaveClient(std::string name, std::string surname) = 0;
    
    virtual void removeProduct(std::string name) = 0;
    virtual void setProductAmount(std::string name, int amount) = 0;
    virtual void increaseProductAmount(std::string name) = 0;
    virtual void decreaseProductAmount(std::string name) = 0;

    virtual unsigned int getNumberOfUnassignedEmployees() const noexcept = 0;
    virtual unsigned int getNumberOfDeactivatedCounters() const noexcept = 0;
    virtual unsigned int getNumberOfActivatedCounters() const noexcept = 0;
    virtual unsigned int getNumberOfClients() const noexcept = 0;
    virtual unsigned int getNumberOfProducts() const noexcept = 0;

    virtual void generateEmployees(int numberOfEmployees, std::ofstream &outputFile) = 0;
    virtual void assignEmployeesToCounters(int numberOfEmployees, std::ofstream &outputFile) = 0;
    virtual void chooseCounterByClient(std::vector<std::unique_ptr<Client>>::iterator iter) = 0;

    virtual void printAllInfo(std::ofstream &outputFile) const = 0;
    virtual void printUnassignedEmployees(std::ofstream &outputFile) const = 0;
    virtual void printDeactivatedCounters(std::ofstream &outputFile) const = 0;
    virtual void printActivatedCounters(std::ofstream &outputFile) const = 0;
    virtual void printClients(std::ofstream &outputFile) const = 0;
    virtual void printProducts(std::ofstream &outputFile) const = 0;

    virtual ~ShopInterface() = 0;
};

#endif

