#include "shop.h"
#include "file_manager.h"
#include "exceptions/file_opening_exception.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

int main(int argc, char** argv){

    std::string output_file_path = "data/output_file.txt";
    std::string info_file_path="data/info.txt";
    std::string products_file_path = "data/products.txt";
    std::string counters_file_path = "data/counters.txt";
    int iteration_number = 10;

    std::cout << output_file_path << info_file_path << products_file_path << counters_file_path << iteration_number;

    std::ofstream outputFile(output_file_path);

    Shop s;
    
    FileManager DataFileInfo(info_file_path);
    FileManager DataFileProducts(products_file_path);
    FileManager DataFileCounters(counters_file_path);

    try {
        DataFileInfo.readShopInfo();
    } catch (FileOpeningException& exc){
        std::cerr << exc.getInfo() << std::endl;
    }

    try {
        DataFileProducts.readProducts(s);
    } catch (FileOpeningException& exc){
        std::cerr << exc.getInfo() << std::endl;
    }

    try {
        DataFileCounters.readCounters(s);
    } catch (FileOpeningException& exc){
        std::cerr << exc.getInfo() << std::endl;
    }

    s.startSimulation(iteration_number, outputFile);
    system("pause");
    return 0;
}
