#include "wrong_data_from_file_exception.h"
#include <string>

WrongDataFileException::WrongDataFileException(std::string _expected_data, std::string _recived_data) : CustomException() {
    expected_data = _expected_data;
    recived_data = _recived_data;
}

std::string WrongDataFileException::getInfo() const {
    return "Wrong data file has been imported. Choose propper data file to fit import.";
}