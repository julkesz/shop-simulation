#ifndef PERSON_H
#define PERSON_H
#include "interfaces/person_interface.h"

class Person: public PersonInterface{
public:
    Person(std::string nm, std::string snm);
    virtual ~Person(){};

    int getId() const noexcept override;
    std::string getName() const noexcept override;
    std::string getSurname() const noexcept override;
    void setName(std::string nm) noexcept override;
    void setSurname(std::string snm) noexcept override;

    virtual std::string getPosition() const noexcept = 0;
protected:
    int id;
    std::string name;
    std::string surname;
};

#endif
