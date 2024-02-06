#ifndef EMPLOYEE_EXISTS_EXCEPTION_H
#define EMPLOYEE_EXISTS_EXCEPTION_H
#include "custom_exception.h"

class EmployeeExistsException: public CustomException
{
    public: 
        EmployeeExistsException(std::string nm, std::string snm);
        std::string getInfo() const;
    private:
        std::string name;
        std::string surname;
};

#endif
