#ifndef NOT_ENOUGH_COUNTERS_EXCEPTION_H
#define NOT_ENOUGH_COUNTERS_EXCEPTION_H
#include "custom_exception.h"
#include <string>

class NotEnoughCountersException: public CustomException
{
public: 
    NotEnoughCountersException(int w, int c);
    std::string getInfo() const;
private:
    int wanted;
    int current;

};

#endif