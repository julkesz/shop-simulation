#include "employee_exists_exception.h"

EmployeeExistsException::EmployeeExistsException(std::string nm, std::string snm):CustomException(){
    name = nm;
    surname = snm;
}

std::string EmployeeExistsException::getInfo() const{
    return "Employee " + name + " " + surname + " has already existed!";
}