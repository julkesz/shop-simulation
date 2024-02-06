#include "person.h"

Person::Person(std::string nm, std::string snm): name(nm), surname(snm), id(0){};

int Person::getId() const noexcept{
    return id;
}

std::string Person::getName() const noexcept{
    return name;
}

std::string Person::getSurname() const noexcept{
    return surname;
}

void Person::setName(std::string nm) noexcept{
    name=nm;
}

void Person::setSurname(std::string snm) noexcept{
    surname=snm;
}