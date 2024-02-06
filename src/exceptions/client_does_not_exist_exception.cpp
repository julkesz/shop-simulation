#include "client_does_not_exist_exception.h"
#include <cstring>

ClientDoesNotExistException::ClientDoesNotExistException(std::string nm, std::string snm):CustomException(){
    name = nm;
    surname = snm;
}

std::string ClientDoesNotExistException::getInfo() const{
    return "Client " + name + " " + surname + " does not exist!";
}
