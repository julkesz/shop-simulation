#include "product_does_not_exist_exception.h"

ProductDoesNotExistException::ProductDoesNotExistException(std::string nm):CustomException(){
    name = nm;
}

std::string ProductDoesNotExistException::getInfo() const{
    return "Porduct " + name + " does not exist!";
}