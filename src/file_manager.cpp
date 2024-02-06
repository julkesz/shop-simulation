#include "file_manager.h"
#include <fstream>
#include <iostream>
#include "product.h"

#include "exceptions/file_opening_exception.h"


FileManager::FileManager(std::string fn):fileName(fn) {}

void FileManager::readShopInfo() {
    std::ifstream data;
    try {
        data.open(fileName);
    }
    catch (...)
    {
        throw FileOpeningException(fileName);
    }

    std::string line = "";
    while (!data.eof()) {
        std::getline(data, line);

        if (line == "$$ShopInfo") {
            std::getline(data, line); //pobieramy kolejn� linijk� z pliku
            while (line != ";") {
                std::cout << "Welcome to " << line << "!" << '\n' << '\n' << '\n' << "Feel free to contact our service team anytime" << '\n' << '\n' << std::endl;
                std::getline(data, line);
            }
        }
    }
    data.close();
    std::cout << '\n' << "End-of-file reached.." << std::endl;

}


void FileManager::readProducts(Shop& s) {

    std::ifstream data;
    try {
        data.open(fileName);
    }
    catch (...)
    {
        throw FileOpeningException(fileName);
    }

    std::string line = "";
    while (!data.eof()) {
        std::getline(data, line);

        if (line == "$$Product") {
            std::cout << '\n' << "Product stock list: " << '\n' << std::endl;
            std::getline(data, line); 
            while (line != ";") {
                std::string word = "";
                std::vector<std::string> wordsInLine = {};
                for (auto x : line) 
                {
                    if (x == ' ')
                    {
                        wordsInLine.push_back(word);
                        word.erase();

                    }
                    else {
                        word = word + x;

                    }
                }
                wordsInLine.push_back(word); 
                word.erase();

                std::cout << "Stock amount: " << wordsInLine[0] << std::endl;
                std::cout << "Product: " << wordsInLine[1] << std::endl;
                std::cout << "Price: " << wordsInLine[2] << std::endl;
                std::cout << "Tax type: " << wordsInLine[3] << '\n' << std::endl;

                std::string dolars = "";
                std::string cents = "";
                for (auto x : wordsInLine[2]) 
                {
                    if (x == '.')
                    {
                        dolars = word;
                        word.erase();
                    }
                    else {
                        word = word + x;
                    }
                }
                cents = word;
                s.addProduct(wordsInLine[1], std::stoi(dolars), std::stoi(cents), std::stoi(wordsInLine[3]), std::stoi(wordsInLine[0]));
                std::getline(data, line); 
            }
                
        }
        
    }

data.close();
std::cout << '\n' << "End-of-file reached.." << std::endl;

}


void FileManager::readCounters(Shop& s) {

    std::ifstream data;
    try {
        data.open(fileName);
    }
    catch (...)
    {
        throw FileOpeningException(fileName);
    }

    std::string line = "";
    while (!data.eof()) {
        std::getline(data, line);

    if (line == "$$Counter") {
        std::cout << '\n' << "Counter list: " << '\n' << std::endl;
        std::getline(data, line); 
        while (line != ";") {
            std::string word = "";
            std::vector<std::string> wordsInLine = {};

            for (auto x : line) 
            {
                if (x == ' ')
                {
                    wordsInLine.push_back(word);
                    word.erase();

                }
                else {
                    word = word + x;

                }

            }

            wordsInLine.push_back(word); 


                std::cout << "ID: " << wordsInLine[0] << std::endl;
                std::cout << "Cash amount: " << wordsInLine[1] << '\n' << std::endl;

                std::string dolars = "";
                std::string cents = "";
                //konwersja ceny w formacie str na oddzielne str dla dolar�w i cent�w
                for (auto x : wordsInLine[1]) //rozbicie linijki na pojedy�cze s�owa
                {
                    if (x == '.')
                    {
                        dolars = word;
                        word.erase();
                    }
                    else {
                        word = word + x;
                    }
                }
                cents = word;


                s.addCounter(std::stoi(dolars), std::stoi(cents));
            
            std::getline(data, line); //kolejna linijka
        }
    }
}

data.close();
std::cout << '\n' << "End-of-file reached.." << std::endl;

}



std::string FileManager::readNthLine(unsigned int lineNumber)
{
    std::ifstream in(fileName.c_str());

    std::string s;
    s.reserve(50);

    for (int i = 0; i < lineNumber; ++i)
        std::getline(in, s);

    std::getline(in, s);
    return s;
}