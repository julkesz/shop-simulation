#include "shop.h"
#include "file_manager.h"
#include "exceptions/file_opening_exception.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

int main(int argc, char** argv){

    if(argc != 6)
    {
        std::cerr << "Incorrect number of command line arguments - expected 6, got " << argc << std::endl;
        return 1;
    }

    std::string info_file_path="";
    std::string output_file_path = "";
    std::string products_file_path = "";
    std::string counters_file_path = "";
    int iteration_number = 0;

    std::cout << argc
        << " arguments have been passed." << "\n";

    std::stringstream stream;
    stream << argv[1];
    stream >> output_file_path;
    stream.clear();

    stream << argv[2];
    stream >> info_file_path;
    stream.clear();

    stream << argv[3];
    stream >> products_file_path;
    stream.clear();

    stream << argv[4];
    stream >> counters_file_path;
    stream.clear();

    stream << argv[5];
    stream >> iteration_number;
    stream.clear();

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
