#ifndef GREATER_MONEY_SUBSTRACTION_EXCEPTION_H
#define GREATER_MONEY_SUBSTRACTION_EXCEPTION_H
#include "custom_exception.h"
#include "../currency.h"

class GreaterMoneySubstractionException: public CustomException
{
    public: 
        GreaterMoneySubstractionException(Currency amntH, Currency amntP);
        std::string getInfo() const;
    private:
        Currency amountHave;
        Currency amountToPay;
};

#endif