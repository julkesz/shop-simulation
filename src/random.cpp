#include "random.h"
#include "file_manager.h"
#include <chrono>
#include <random>


std::string Random::getRandomName(){
    int lineNumber = getRandomInteger(1,100);
    FileManager f("data/names.txt");
    std::string name = f.readNthLine(lineNumber);

    return name; 
}

std::string Random::getRandomSurname(){
    int lineNumber = getRandomInteger(1,100);
    FileManager f("data/surnames.txt");
    std::string surname = f.readNthLine(lineNumber);

    return surname; 
}

Product Random::getRandomProduct(const std::map<Product, int>& products){
    int n = getRandomInteger(0, products.size()-1);
    auto it = products.begin();
    std::advance(it, n);
    return it-> first;
}

int Random::getRandomInteger(int min, int max){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<> dist(min, max);
    return dist(generator);
}