#ifndef EMPLOYEE_DOES_NOT_EXIST_EXCEPTION_H
#define EMPLOYEE_DOES_NOT_EXIST_EXCEPTION_H
#include "custom_exception.h"
#include <string>

class EmployeeDoesNotExistException: public CustomException
{
    public: 
        EmployeeDoesNotExistException(std::string nm, std::string snm);
        std::string getInfo() const;
    private:
        std::string name;
        std::string surname;
};

#endif