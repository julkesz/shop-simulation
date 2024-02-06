#include "client_exists_exception.h"

ClientExistsException::ClientExistsException(std::string nm, std::string snm):CustomException(){
    name = nm;
    surname = snm;
}

std::string ClientExistsException::getInfo() const{
    return "Client " + name + " " + surname + " has already existed!";
}