#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
#include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

#include "shop.h"
#include "random.h"
#include "regular_client.h"

#include "exceptions/employee_exists_exception.h"
#include "exceptions/employee_does_not_exist_exception.h"
#include "exceptions/client_exists_exception.h"
#include "exceptions/client_does_not_exist_exception.h"
#include "exceptions/product_exists_exception.h"
#include "exceptions/product_does_not_exist_exception.h"
#include "exceptions/no_active_counter_exception.h"
#include "exceptions/not_enough_counters_exception.h"

#include <algorithm>

void Shop::startSimulation(unsigned int iterationNumber, std::ofstream &outputFile){
    Random r;

    std::cout << "################################################" << std::endl;
    std::cout << "PREPARE PHASE 1: GENERATING EMPLOYEES" << std::endl;
    outputFile << "################################################" << std::endl;
    outputFile << "PREPARE PHASE 1: GENERATING EMPLOYEES"<< std::endl;
    int numberOfEmployees = r.getRandomInteger(2,5);
    generateEmployees(numberOfEmployees, outputFile);

    std::cout << std::endl << std::endl;
    std::cout<< "################################################" << std::endl;
    std::cout<< "PREPARE PHASE 2: ASSINGING TWO EMPLOYEES TO THE COUNTERS" << std::endl;
    outputFile << std::endl << std::endl;
    outputFile << "################################################" << std::endl;
    outputFile << "PREPARE PHASE 2: ASSINGING TWO EMPLOYEES TO THE COUNTERS" << std::endl;
    try{
    assignEmployeesToCounters(2, outputFile);
    } catch (NotEnoughCountersException& exc){
                std::cerr << exc.getInfo() << std::endl;
    }
    std::cout << std::endl << std::endl;
    std::cout<< "################################################" << std::endl;
    std::cout<< "################## SHOP INFO ###################" << std::endl;
    outputFile << std::endl << std::endl;
    outputFile << "################################################" << std::endl;
    outputFile << "################## SHOP INFO ###################" << std::endl;
    printAllInfo(outputFile);

    std::cout << std::endl << std::endl;
    std::cout << "################################################" << std::endl;
    std::cout << "################## START SIMULATION ###################" << std::endl;
    outputFile << std::endl << std::endl;
    outputFile << "################################################" << std::endl;
    outputFile << "################## START SIMULATION ###################" << std::endl;

    for(int i = 0; i < iterationNumber; i++){
        std::cout << "################################################" << std::endl;
        std::cout << "ITERATION NR: "<< i << std::endl;
        std::cout << std::endl << std::endl;
        std::cout << "PHASE 1: NEW CLIENTS ENTERING" << std::endl;
        outputFile << "################################################" << std::endl;
        outputFile <<"ITERATION NR: "<< i << std::endl;
        outputFile <<std::endl<<std::endl;
        outputFile << "PHASE 1: NEW CLIENTS ENTERING"<< std::endl;
        int numberOfNewClients = r.getRandomInteger(0,3);
        for(int j = 0; j != numberOfNewClients; j++){
            int typeOfCLient = r.getRandomInteger(0,1);
            try{
                enterClient(r.getRandomName(), r.getRandomSurname(), r.getRandomInteger(10,100), r.getRandomInteger(0,99), typeOfCLient);
            } catch (ClientExistsException& exc){
                std::cerr << exc.getInfo() << std::endl;
            }
            std::cout << *(clients[clients.size()-1]) << " entered." << std::endl;
            std::cout << "He/She has " << (*(clients[clients.size()-1])).getMoney() << " and want to buy " << (*(clients[clients.size()-1])).getNumberOfWantedProducts() << " products." << std::endl;
            outputFile << *(clients[clients.size()-1]) << " entered." << std::endl;
            outputFile << "He/She has " << (*(clients[clients.size()-1])).getMoney() << " and want to buy " << (*(clients[clients.size()-1])).getNumberOfWantedProducts() << " products." << std::endl;
            sleep(2);
        }
        std::cout << std::endl << std::endl;
        std::cout << "PHASE 2: CLIENTS ARE CHOOSING RODUCTS: " << std::endl;
        outputFile << std::endl << std::endl;
        outputFile << "PHASE 2: CLIENTS ARE CHOOSING RODUCTS: " << std::endl;
        for (std::vector<std::unique_ptr<Client>>::iterator it = clients.begin(); it != clients.end();){
            if ( ((*it)->getNumberOfProducts() < (*it)->getNumberOfWantedProducts()) && (this->getNumberOfProducts() > 0) ){
                Product prod = r.getRandomProduct(products);
                if ( ((*it)->getBasketValue() + prod.getPriceGross()) <= (*it)->getMoney()){
                    (*it)->addProduct(prod);
                    products[prod]--;
                    if(products[prod] == 0){
                        products.erase(prod);
                    }
                    std::cout << (**it) << " took " <<  prod << std::endl;
                    outputFile << (**it) << " took " <<  prod << std::endl;
                    if ((*it)->getNumberOfProducts() == (*it)->getNumberOfWantedProducts()){
                        try {
                            chooseCounterByClient(it);
                        } catch (NoActiveCounterException& exc){
                            std::cerr << exc.getInfo() << std::endl;
                        }
                    } else {
                        it++;
                    }
                } else{
                    try {
                        chooseCounterByClient(it);
                    } catch (NoActiveCounterException& exc){
                        std::cerr << exc.getInfo() << std::endl;
                    }
                }
            } else{
                try {
                    chooseCounterByClient(it);
                } catch (NoActiveCounterException& exc){
                    std::cerr << exc.getInfo() << std::endl;
                }
            }
            sleep(2);
        }
        std::cout << std::endl << std::endl;
        std::cout << "PHASE 3: CLIENTS ARE PAYING: "<< std::endl;
        outputFile <<std::endl << std::endl;
        outputFile <<"PHASE 3: CLIENTS ARE PAYING: "<< std::endl;
        for (auto& cntr : activatedCounters){
            std::cout<< std::endl;
            outputFile << std::endl;
            cntr.get()->serveFirstClient(outputFile);
            sleep(2);
        }
        std::cout << std::endl << std::endl << std::endl;
        outputFile << std::endl << std::endl << std::endl;
        sleep(3);
    }

    std::cout << "################################################"<< std::endl;
    std::cout << "################## SHOP INFO ###################"<< std::endl;
    outputFile << "################################################"<< std::endl;
    outputFile << "################## SHOP INFO ###################"<< std::endl;
    printAllInfo(outputFile);
}

void Shop::addEmployee(std::string name, std::string surname){
    auto const it = std::find_if(unassignedEmployees.begin(), unassignedEmployees.end(), [&](auto const& empl) { return empl->getName() == name && empl->getSurname() == surname; });
    if( it != unassignedEmployees.end())
    {
        throw EmployeeExistsException(name, surname);
    }
    std::unique_ptr<Employee> empl = std::make_unique<Employee>(name, surname);
    unassignedEmployees.push_back(std::move(empl));
}

void Shop::removeEmployee(std::string name, std::string surname){
    auto const it = std::find_if(unassignedEmployees.begin(), unassignedEmployees.end(), [&](auto const& empl) { return empl->getName() == name && empl->getSurname() == surname; });
    if( it != unassignedEmployees.end())
    {
        unassignedEmployees.erase(it);
    } else {
        throw EmployeeDoesNotExistException(name, surname);
    }
}

void Shop::addCounter(unsigned int dollars, unsigned int cents) noexcept {
    std::unique_ptr<Counter> cntr = std::make_unique<Counter>(Currency(dollars, cents));
    deactivatedCounters.push_back(std::move(cntr));
}

void Shop::enterClient(std::string name, std::string surname, unsigned int dollars, unsigned int cents, int type){
    auto const it = std::find_if(clients.begin(), clients.end(), [&](auto const& clnt) { return clnt->getName() == name && clnt->getSurname() == surname; });
    if( it != clients.end())
    {
        throw ClientExistsException(name, surname);
    }
    if ( type == 0){
        std::unique_ptr<Client> clnt = std::make_unique<Client>(name, surname, Currency(dollars, cents));
        clients.push_back(std::move(clnt));
    } else {
        std::unique_ptr<Client> clnt = std::make_unique<RegularClient>(name, surname, Currency(dollars, cents));
        clients.push_back(std::move(clnt));
    }
}

void Shop::leaveClient(std::string name, std::string surname){
    auto const it = std::find_if(clients.begin(), clients.end(), [&](auto const& clnt) { return clnt->getName() == name && clnt->getSurname() == surname; });
    if( it != clients.end())
    {
        clients.erase(it);
    } else {
        throw ClientDoesNotExistException(name, surname);
    }
}

void Shop::addProduct(std::string nm, unsigned int dollars, unsigned int cents, int taxCat, int amount){
    Product prod(nm, Currency(dollars, cents), Product::TaxCategory(taxCat));
    const auto ret = products.insert({prod,amount});
    if (!ret.second) {
         throw ProductExistsException(nm);
    }
}

void Shop::removeProduct(std::string name){
    Product prod(name);
    auto it = products.find(Product(name));
    if (it != products.end()){
        products.erase(prod);
    } else {
        throw ProductDoesNotExistException(name);
    }
}

unsigned int Shop::getNumberOfUnassignedEmployees() const noexcept{
    return unassignedEmployees.size();
}

unsigned int Shop::getNumberOfDeactivatedCounters() const noexcept{
    return deactivatedCounters.size();
}

unsigned int Shop::getNumberOfActivatedCounters() const noexcept{
    return activatedCounters.size();
}

unsigned int Shop::getNumberOfClients() const noexcept{
     return clients.size();
}

unsigned int Shop::getNumberOfProducts() const noexcept{
    unsigned int sumOfProducts = 0;
    for (const auto& prod : products){
        sumOfProducts += prod.second;
    }
    return sumOfProducts;
}

void Shop::setProductAmount(std::string name, int amount){
    Product prod(name);
    auto it = products.find(Product(name));
    if (it != products.end()){
        products[prod] = amount;
    } else {
        throw ProductDoesNotExistException(name);
    }
}

void Shop::increaseProductAmount(std::string name){
    Product prod(name);
    auto it = products.find(Product(name));
    if (it != products.end()){
        products[prod]++;
    } else {
        throw ProductDoesNotExistException(name);
    }
}

void Shop::decreaseProductAmount(std::string name){
    Product prod(name);
    auto it = products.find(Product(name));
    if (it != products.end()){
        products[prod]--;
    } else {
        throw ProductDoesNotExistException(name);
    }
}

void Shop::chooseCounterByClient(std::vector<std::unique_ptr<Client>>::iterator iter){
    if( activatedCounters.empty() ){
        throw NoActiveCounterException();
    }

    auto retval = std::move(*iter);
    clients.erase(iter);

    std::sort(activatedCounters.begin(), activatedCounters.end(), [](const std::unique_ptr<Counter> &cntr1, const std::unique_ptr<Counter> &cntr2) {
        return cntr1->getNumberOfClients() < cntr2->getNumberOfClients();
    });  

    std::vector<std::unique_ptr<Counter>>::iterator it = activatedCounters.begin();
    (*it)->addClient(std::move(retval));
}

void Shop::generateEmployees(int numberOfEmployees, std::ofstream &outputFile) {
    Random r;
    for(int j = 0; j != numberOfEmployees; j++){
    try{
        addEmployee(r.getRandomName(), r.getRandomSurname());
    } catch (EmployeeExistsException& exc){
        std::cerr << exc.getInfo() << std::endl;
    }
    std::cout << *(unassignedEmployees[unassignedEmployees.size()-1]) << " has been added." << std::endl;
    outputFile << *(unassignedEmployees[unassignedEmployees.size()-1]) << " has been added." << std::endl;
}
}


void Shop::assignEmployeesToCounters(int numberOfEmployees, std::ofstream &outputFile){
    if (numberOfEmployees > deactivatedCounters.size()){
        throw NotEnoughCountersException(numberOfEmployees, deactivatedCounters.size());
    }
    std::vector<std::unique_ptr<Employee>>::iterator ite = unassignedEmployees.begin();
    std::vector<std::unique_ptr<Counter>>::iterator itc = deactivatedCounters.begin();
    for(int j = 0; j < numberOfEmployees; j++){
        (*itc)->assignEmployee(std::move(*ite));
        unassignedEmployees.erase(ite);
        activatedCounters.push_back(std::move(*itc));
        deactivatedCounters.erase(itc);
        std::cout<< *(activatedCounters[activatedCounters.size()-1]) << std::endl;
        outputFile << *(activatedCounters[activatedCounters.size()-1]) << std::endl;
    }
}

void Shop::printUnassignedEmployees(std::ofstream &outputFile) const{
    for(const auto& p : unassignedEmployees){
        std::cout << *p << std::endl;
        outputFile << *p << std::endl;
    }
}

void Shop::printActivatedCounters(std::ofstream &outputFile) const{
    for(const auto& cntr : activatedCounters){
        std::cout << *cntr << std::endl;
        outputFile << *cntr << std::endl;
    }
}

void Shop::printDeactivatedCounters(std::ofstream &outputFile) const{
    for(const auto& cntr : deactivatedCounters){
        std::cout << *cntr << std::endl;
        outputFile << *cntr << std::endl;
    }
}

void Shop::printClients(std::ofstream &outputFile) const{
    for(const auto& p : clients){
        std::cout << *p << std::endl;
        outputFile << *p << std::endl;
    }
}

void Shop::printProducts(std::ofstream &outputFile) const{
    for (const auto& prod : products){
        std::cout << prod.first << ", Amount: " << prod.second << std::endl;
        outputFile << prod.first << ", Amount: " << prod.second << std::endl;
    }
}

void Shop::printAllInfo(std::ofstream &outputFile) const{
    if ( !unassignedEmployees.empty() ){
        std::cout << "UNASSIGNED EMPLOYEES: "<< std::endl;
        outputFile << "UNASSIGNED EMPLOYEES: "<< std::endl;
        printUnassignedEmployees(outputFile);
    }
    if ( !deactivatedCounters.empty() ){
        std::cout << std::endl;
        outputFile << std::endl;
        std::cout << "DEACTIVATED COUNTERS: "<< std::endl;
        outputFile << "DEACTIVATED COUNTERS: "<< std::endl;
        printDeactivatedCounters(outputFile);
    }
    if ( !activatedCounters.empty() ){
        std::cout<< std::endl;
        outputFile << std::endl;
        std::cout << "ACTIVATED COUNTERS: "<< std::endl;
        outputFile << "ACTIVATED COUNTERS: "<< std::endl;
        printActivatedCounters(outputFile);
    }
    if ( !products.empty() ){
        std::cout<< std::endl;
        outputFile << std::endl;
        std::cout << "PRODUCTS: "<< std::endl;
        outputFile << "PRODUCTS: "<< std::endl;
        printProducts(outputFile);
    }
    if ( !clients.empty() ){
        std::cout<< std::endl;
        outputFile << std::endl;
        std::cout << "CLIENTS: "<< std::endl;
        outputFile << "CLIENTS: "<< std::endl;
        printClients(outputFile);
    }
}