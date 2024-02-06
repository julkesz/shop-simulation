#include "employee.h"
#include <iostream>

int Employee::NUMBER_OF_EMPLOYEES=0;

Employee::Employee(std::string nm, std::string snm): Person(nm, snm){
    id=++NUMBER_OF_EMPLOYEES;
};

std::string Employee::getPosition() const noexcept {
    return "Employee";
}

std::ostream& operator<<(std::ostream& os, const Employee& empl)
{
    os << "Employee "<< empl.id << ": "<< empl.name <<" " << empl.surname;
    return os;
}
