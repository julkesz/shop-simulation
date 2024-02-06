#ifndef CLIENT_DOES_NOT_EXIST_EXCEPTION_H
#define CLIENT_DOES_NOT_EXIST_EXCEPTION_H
#include "custom_exception.h"
#include <string>

class ClientDoesNotExistException: public CustomException
{
    public: 
        ClientDoesNotExistException(std::string nm, std::string snm);
        std::string getInfo() const;
    private:
        std::string name;
        std::string surname;
};

#endif
