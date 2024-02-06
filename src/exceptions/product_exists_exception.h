#ifndef PRODUCT_EXISTS_EXCEPTION_H
#define PRODUCT_EXISTS_EXCEPTION_H
#include "custom_exception.h"
#include <string>

class ProductExistsException: public CustomException
{
    public: 
        ProductExistsException(std::string nm);
        std::string getInfo() const;
    private:
        std::string name;
};

#endif