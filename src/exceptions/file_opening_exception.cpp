#include "file_opening_exception.h"

FileOpeningException::FileOpeningException(std::string file_to_open) : CustomException() {
    file_path = file_to_open;
}

std::string FileOpeningException::getInfo() const {
    return "Trying to open file at path: " + file_path + " and failed. Make sure the path is propper, and the file exist at given location.";
}