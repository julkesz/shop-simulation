#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "person.h"


class Employee: public Person{
public:
    Employee(std::string nm, std::string snm);

    std::string getPosition() const noexcept override;

    friend std::ostream& operator<<(std::ostream& os, const Employee& empl);
private:
    static int NUMBER_OF_EMPLOYEES;
};

#endif