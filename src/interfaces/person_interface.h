#ifndef PERSON_INTERFACE_H
#define PERSON_INTERFACE_H
#include <string>

class PersonInterface {
public:
    virtual int getId() const noexcept = 0;
    virtual std::string getName() const noexcept = 0;
    virtual std::string getSurname() const noexcept = 0;
    virtual void setName(std::string nm) noexcept = 0;
    virtual void setSurname(std::string snm) noexcept = 0;
    virtual std::string getPosition() const noexcept = 0;

    virtual ~PersonInterface() = 0;
};

#endif