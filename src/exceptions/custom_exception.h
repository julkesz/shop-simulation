#ifndef CUSTOM_EXCEPTION_H
#define CUSTOM_EXCEPTION_H
#include <string>

class CustomException{
public:
    virtual std::string getInfo() const = 0;
    virtual ~CustomException(){}
};

#endif