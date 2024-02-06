#ifndef FILE_OPENING_EXCEPTION_H
#define FILE_OPENING_EXCEPTION_H
#include "custom_exception.h"

class FileOpeningException : public CustomException
{
public:
    FileOpeningException(std::string file_to_open);
    std::string getInfo() const;
private:
    std::string file_path;
};

#endif