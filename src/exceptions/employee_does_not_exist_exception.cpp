#include "employee_does_not_exist_exception.h"

EmployeeDoesNotExistException::EmployeeDoesNotExistException(std::string nm, std::string snm):CustomException(){
    name = nm;
    surname = snm;
}

std::string EmployeeDoesNotExistException::getInfo() const{
    return "Employee " + name + " " + surname + " does not exist!";
}