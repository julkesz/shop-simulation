#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H
#include "interfaces/file_manager_interface.h"

class FileManager: public FileManagerInterface {
public:
    FileManager(std::string fn);
    void readProducts(Shop& s) override;
    void readCounters(Shop& s) override;
    void readShopInfo() override;
    std::string readNthLine(unsigned int lineNumber) override;
private:
    std::string fileName;
};


#endif