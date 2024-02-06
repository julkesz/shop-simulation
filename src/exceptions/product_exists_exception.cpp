#include "product_exists_exception.h"

ProductExistsException::ProductExistsException(std::string nm):CustomException(){
    name = nm;
}

std::string ProductExistsException::getInfo() const{
    return "Porduct " + name + " has already existed!";
}