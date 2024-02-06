#include "greater_money_substraction_exception.h"

GreaterMoneySubstractionException::GreaterMoneySubstractionException(Currency amntH, Currency amntP) : CustomException(){
    amountHave = amntH;
    amountToPay = amntP;
}

std::string GreaterMoneySubstractionException::getInfo() const{
    return "Trying to substract " + std::to_string(amountHave.getDollars()) + " dollars and " + std::to_string(amountHave.getCents()) + " cents from " + std::to_string(amountHave.getDollars()) + " dollars and " + std::to_string(amountHave.getCents()) + " cents.";
}