#ifndef COUNTER_H
#define COUNTER_H
#include "interfaces/counter_interface.h"
#include <queue>


class Counter: public CounterInterface{
public:
    Counter(Currency mon = Currency(0,0));
    Currency getMoney() const noexcept override;
    std::string getAssignedEmployee() const noexcept override;
    void setMoney(Currency mon) noexcept override;
    void receiveMoney(Currency mon) noexcept override;
    void assignEmployee(std::unique_ptr<Employee> empl) noexcept override;
    void addClient(std::unique_ptr<Client> clnt) noexcept override;
    int getNumberOfClients() const noexcept override;
    void serveFirstClient(std::ofstream &outputFile) override;

    friend std::ostream& operator<<(std::ostream& os, const Counter& cntr);

private:
    static int NUMBER_OF_COUNTERS;
    int id;
    Currency money;
    std::unique_ptr<Employee> assignedEmployee;
    std::queue<std::unique_ptr<Client>> lineOfClients;
};

#endif