#ifndef PRODUCT_DOES_NOT_EXIST_EXCEPTION_H
#define PRODUCT_DOES_NOT_EXIST_EXCEPTION_H
#include "custom_exception.h"
#include <string>

class ProductDoesNotExistException: public CustomException
{
    public: 
        ProductDoesNotExistException(std::string nm);
        std::string getInfo() const;
    private:
        std::string name;

};

#endif