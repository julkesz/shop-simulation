#ifndef COUNTER_INTERFACE_H
#define COUNTER_INTERFACE_H
#include "../currency.h"
#include "../employee.h"
#include "../client.h"
#include <memory>

class CounterInterface {
public:
    virtual Currency getMoney() const noexcept = 0;
    virtual std::string getAssignedEmployee() const noexcept = 0;
    virtual void setMoney(Currency mon) noexcept = 0;
    virtual void receiveMoney(Currency mon) noexcept = 0;
    virtual void assignEmployee(std::unique_ptr<Employee> empl) noexcept = 0;
    virtual void addClient(std::unique_ptr<Client> clnt) noexcept = 0 ;
    virtual int getNumberOfClients() const noexcept = 0;
    virtual void serveFirstClient(std::ofstream &outputFile) = 0;

    virtual ~CounterInterface() = 0;
};

#endif