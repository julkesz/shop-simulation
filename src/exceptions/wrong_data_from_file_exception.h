#ifndef WRONG_DATA_FILE_EXCEPTION_H
#define WRONG_DATA_FILE_EXCEPTION_H
#include "custom_exception.h"

class WrongDataFileException : public CustomException
{
public:
    WrongDataFileException(std::string expected_data, std::string recived_data);
    std::string getInfo() const;
private:
    std::string expected_data;
    std::string recived_data;
};

#endif