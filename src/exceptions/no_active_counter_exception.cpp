#include "no_active_counter_exception.h"

NoActiveCounterException::NoActiveCounterException():CustomException(){}

std::string NoActiveCounterException::getInfo() const{
    return "No active counter!";
}