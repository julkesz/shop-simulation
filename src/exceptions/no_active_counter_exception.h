#ifndef NO_ACTIVE_COUNTER_EXCEPTION_H
#define NO_ACTIVE_COUNTER_EXCEPTION_H
#include "custom_exception.h"
#include <string>

class NoActiveCounterException: public CustomException
{
    public: 
        NoActiveCounterException();
        std::string getInfo() const;
};

#endif