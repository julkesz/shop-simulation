#include "counter.h"

int Counter::NUMBER_OF_COUNTERS=0;

Counter::Counter(Currency mon):money(mon) {
    id=++NUMBER_OF_COUNTERS;
};

Currency Counter::getMoney() const noexcept{
    return money;
}

std::string Counter::getAssignedEmployee() const noexcept{
    return assignedEmployee->getName() + assignedEmployee->getSurname();
}

void Counter::setMoney(Currency mon) noexcept {
    money = mon;
}

void Counter::receiveMoney(Currency mon) noexcept{
    money += mon;
}

void Counter::assignEmployee(std::unique_ptr<Employee> empl) noexcept{
    assignedEmployee = std::move(empl);
}

void Counter::addClient(std::unique_ptr<Client> clnt) noexcept{
    lineOfClients.push(std::move(clnt));
}

int Counter::getNumberOfClients() const noexcept{
    return lineOfClients.size();
}

void Counter::serveFirstClient(std::ofstream &outputFile) {
    if(!lineOfClients.empty()){
        Currency totalPrice = lineOfClients.front()->printBill(outputFile);
        lineOfClients.front()->pay(totalPrice);
        this->receiveMoney(totalPrice);
        lineOfClients.pop();
    }
}

std::ostream& operator<<(std::ostream& os, const Counter& cntr) {
    os << "Counter " << cntr.id ;
    if (cntr.assignedEmployee != nullptr) {
        os << ": Assigned employee: " << *cntr.assignedEmployee << ", Size of line: "<< cntr.lineOfClients.size();
    }
    return os;
}