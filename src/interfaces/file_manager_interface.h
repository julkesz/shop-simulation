#ifndef FILE_MANAGER_INTERFACE_H
#define FILE_MANAGER_INTERFACE_H
#include "../shop.h"

class FileManagerInterface {
public:
    virtual void readProducts(Shop& s) = 0;
    virtual void readCounters(Shop& s) = 0;
    virtual void readShopInfo() = 0;
    virtual std::string readNthLine(unsigned int lineNumber) = 0;

    virtual ~FileManagerInterface() = 0;
};


#endif