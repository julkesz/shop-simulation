#ifndef CLIENT_EXISTS_EXCEPTION_H
#define CLIENT_EXISTS_EXCEPTION_H
#include "custom_exception.h"
#include <string>

class ClientExistsException: public CustomException
{
    public: 
        ClientExistsException(std::string nm, std::string snm);
        std::string getInfo() const;
    private:
        std::string name;
        std::string surname;
};

#endif
