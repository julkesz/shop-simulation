#include "currency.h"
#include "exceptions/greater_money_substraction_exception.h"
#include <cmath>

Currency::Currency(unsigned int dlr, unsigned int cnt): dollars(dlr), cents(cnt){};

unsigned int Currency::getDollars() const noexcept{
    return dollars;
}

unsigned int Currency::getCents() const noexcept{
    return cents;
}

Currency& Currency::operator+=(const Currency& curr){
    int sum_of_cents = dollars * 100 + cents + curr.dollars * 100 + curr.cents;

    dollars = sum_of_cents / 100;
    cents = sum_of_cents % 100;
    return (*this);
}

Currency& Currency::operator-=(const Currency& curr){
    if ( *this < curr ){
        throw GreaterMoneySubstractionException(*this,curr); 
    }
    int sum_of_cents = dollars * 100 + cents - ( curr.dollars * 100 + curr.cents );
    dollars = sum_of_cents / 100;
    cents = sum_of_cents % 100;
    return (*this);
}

Currency& Currency::operator*=(const double& multiplier){
    int sum_of_cents =  dollars * 100 + cents;
    int new_sum_of_cents = static_cast<int>(std::round(multiplier * sum_of_cents));
    dollars = new_sum_of_cents / 100;
    cents = new_sum_of_cents % 100;
    return (*this);
}

Currency Currency::operator+(const Currency& curr) const
{
    Currency res = *this;
    res += curr;
    return res;
}

Currency Currency::operator-(const Currency& curr) const
{
    Currency res = *this;
    try {
        res -= curr;
    } catch (GreaterMoneySubstractionException& exc){
        throw;
    }
    return res;
}

Currency Currency::operator*(const double& multiplier) const
{
    Currency res = *this;
    res *= multiplier;
    return res;
}

bool Currency::operator<(const Currency& curr) const{
    return ( dollars < curr.dollars ) || ( dollars == curr.dollars && cents < curr.cents );
}

bool Currency::operator>(const Currency& curr) const{ 
    return curr < *this;
}

bool Currency::operator<=(const Currency& curr) const{
    return !(*this > curr); 
}

bool Currency::operator>=(const Currency& curr) const{ 
    return !(*this < curr); 
}

bool Currency::operator==(const Currency& curr) const{
    return (dollars == curr.dollars && cents == curr.cents);
}

std::ostream& operator<<(std::ostream& os, const Currency& curr)
{
    if(curr.cents < 10){
        os << curr.dollars << ",0" << curr.cents << " USD";
    }else{
        os << curr.dollars << "," << curr.cents << " USD";
    }
    return os;
}
