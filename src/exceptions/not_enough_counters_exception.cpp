#include "not_enough_counters_exception.h"

NotEnoughCountersException::NotEnoughCountersException(int w, int c):CustomException(){
    wanted = w;
    current = c;
}

std::string NotEnoughCountersException::getInfo() const{
    return "Want to assign to " + std::to_string(wanted) + " counters, but have only " + std::to_string(current) + " free counters.";
}