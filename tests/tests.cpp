#include "../src/client.h"
#include "../src/counter.h"
#include "../src/regular_client.h"
#include "../src/employee.h"
#include "../src/product.h"
#include "../src/currency.h"
#include "../src/exceptions/greater_money_substraction_exception.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Client class tests", "[Client]") {
    // Initialize a client with a name, surname, and money
    Client c("John", "Doe", Currency(100,50));

    // Test the getter methods
    REQUIRE(c.getId() == 1);
    REQUIRE(c.getName() == "John");
    REQUIRE(c.getSurname() == "Doe");
    REQUIRE(c.getMoney() == Currency(100,50));
    REQUIRE(c.getNumberOfProducts() == 0);
    REQUIRE(c.getBasketValue() == Currency(0,0));

    // Test the setter methods
    c.setName("Jane");
    c.setSurname("Smith");
    c.setMoney(Currency(50,0));
    REQUIRE(c.getName() == "Jane");
    REQUIRE(c.getSurname() == "Smith");
    REQUIRE(c.getMoney() == Currency(50,0));

    // Test the addProduct method
    Product p1("Product 1", Currency(20,0));
    Product p2("Product 2", Currency(30,0));
    c.addProduct(p1);
    c.addProduct(p2);
    REQUIRE(c.getNumberOfProducts() == 2);
    REQUIRE(c.getBasketValue() == Currency(50,0));

    // Test the printBill method
    std::ofstream outputFile("test.txt");
    REQUIRE(c.printBill(outputFile) == Currency(50,0));

    // Test the pay method
    c.pay(Currency(20,0));
    REQUIRE(c.getMoney() == Currency(30,0));

    // Test the friend operator <<
    std::stringstream ss;
    ss << c;
    REQUIRE(ss.str() == "Client 1: Jane Smith");
}


TEST_CASE("Test Employee class methods", "[Employee]") {
    Employee empl("John", "Doe");
    Employee empl2("Jane", "Doe");

    SECTION("Test getPosition method") {
        REQUIRE(empl.getPosition() == "Employee");
    }

    SECTION("Test getId method") {
        REQUIRE(empl.getId() == 3);
        REQUIRE(empl2.getId() == 4);
    }

    SECTION("Test getName and getSurname methods") {
        REQUIRE(empl.getName() == "John");
        REQUIRE(empl.getSurname() == "Doe");
    }

    SECTION("Test setName and setSurname methods") {
        empl.setName("Mark");
        empl.setSurname("Smith");
        REQUIRE(empl.getName() == "Mark");
        REQUIRE(empl.getSurname() == "Smith");
    }

    SECTION("Test operator<<") {
        std::stringstream ss;
        ss << empl;
        REQUIRE(ss.str() == "Employee 9: John Doe");
    }
}


TEST_CASE("RegularClient - addProduct", "[RegularClient]") {
    RegularClient rc("John", "Doe", Currency(10,50), 20);
    Product p1("Product 1", Currency(5,0));
    Product p2("Product 2", Currency(10,0));

    rc.addProduct(p1);
    rc.addProduct(p2);

    REQUIRE(rc.getBasket().size() == 2);
    REQUIRE(rc.getBasketValue() == Currency(12,00));
}

TEST_CASE("RegularClient - printBill", "[RegularClient]") {
    RegularClient rc("John", "Doe", Currency(10,50), 20);
    Product p1("Product 1", Currency(5,0));
    Product p2("Product 2", Currency(10,0));
    std::ofstream outputFile("test.txt");

    rc.addProduct(p1);
    rc.addProduct(p2);

    Currency price = rc.printBill(outputFile);
    REQUIRE(price == Currency(12,00));

    Currency price2 = rc.printBill(outputFile);
    REQUIRE(price2 == Currency(12,00));
}

TEST_CASE("Test Currency class initialization", "[Currency]") {
    Currency curr1(10, 25);
    REQUIRE(curr1.getDollars() == 10);
    REQUIRE(curr1.getCents() == 25);

    Currency curr2(0, 0);
    REQUIRE(curr2.getDollars() == 0);
    REQUIRE(curr2.getCents() == 0);
}

TEST_CASE("Test Currency class addition", "[Currency]") {
    Currency curr1(10, 25);
    Currency curr2(5, 75);
    Currency curr3 = curr1 + curr2;
    REQUIRE(curr3.getDollars() == 16);
    REQUIRE(curr3.getCents() == 0);
}

TEST_CASE("Test Currency class subtraction", "[Currency]") {
    Currency curr1(10, 25);
    Currency curr2(5, 75);
    Currency curr3 = curr1 - curr2;
    REQUIRE(curr3.getDollars() == 4);
    REQUIRE(curr3.getCents() == 50);

    Currency curr4(5, 50);
    Currency curr5(10, 25);
    REQUIRE_THROWS_AS(curr4 - curr5, GreaterMoneySubstractionException);
}

TEST_CASE("Test Currency class multiplication", "[Currency]") {
    Currency curr1(10, 25);
    Currency curr2 = curr1 * 2.5;
    REQUIRE(curr2.getDollars() == 25);
    REQUIRE(curr2.getCents() == 63);
}

TEST_CASE("Test Currency class comparison operators", "[Currency]") {
    Currency curr1(10, 25);
    Currency curr2(5, 75);
    Currency curr3(10, 25);

    REQUIRE(curr1 > curr2);
    REQUIRE(curr1 >= curr2);
    REQUIRE_FALSE(curr1 < curr2);
    REQUIRE_FALSE(curr1 <= curr2);
    REQUIRE(curr1 == curr3);
}

TEST_CASE("Product class tests", "[Product]") {
    // Test default constructor
    Product p1("");
    REQUIRE(p1.getId() == 1);
    REQUIRE(p1.getName() == "");
    REQUIRE(p1.getPriceNet() == Currency(0, 0));
    REQUIRE(p1.getPriceGross() == Currency(0, 0));
    REQUIRE(p1.getTaxCategory() == ProductInterface::TaxCategory::low);

    // Test constructor with parameters
    Currency c1(10, 50);
    Product p2("Computer", c1, ProductInterface::TaxCategory::high);
    REQUIRE(p2.getId() == 8);
    REQUIRE(p2.getName() == "Computer");
    REQUIRE(p2.getPriceNet() == c1);
    REQUIRE(p2.getPriceGross() == Currency(12, 92));
    REQUIRE(p2.getTaxCategory() == ProductInterface::TaxCategory::high);

    // Test setters
    p2.setName("Laptop");
    REQUIRE(p2.getName() == "Laptop");

    Currency c2(20, 0);
    p2.setPriceNet(c2);
    REQUIRE(p2.getPriceNet() == c2);
    REQUIRE(p2.getPriceGross() == Currency(24, 60));

    p2.setTaxCategory(ProductInterface::TaxCategory::medium);
    REQUIRE(p2.getTaxCategory() == ProductInterface::TaxCategory::medium);
    REQUIRE(p2.getPriceGross() == Currency(21, 60));

    // Test comparison operators
    Product p3("Computer", Currency(10, 50), ProductInterface::TaxCategory::high);
    Product p4("Computer", Currency(20, 0), ProductInterface::TaxCategory::medium);
    Product p5("Laptop", Currency(20, 0), ProductInterface::TaxCategory::medium);

    REQUIRE(p3 == p4);
    REQUIRE(p3 != p5);
    REQUIRE(p4 < p5);
    REQUIRE(p5 > p4);
    REQUIRE(p3 <= p4);
    REQUIRE(p5 >= p4);
}

TEST_CASE("Counter class tests", "[Counter]") {
    // Create a new Counter object with an initial Currency amount of $10
    Counter counter(Currency(10, 0));

    SECTION("Test getMoney() and setMoney()") {
        REQUIRE(counter.getMoney() == Currency(10, 0));
        counter.setMoney(Currency(20, 50));
        REQUIRE(counter.getMoney() == Currency(20, 50));
    }

    SECTION("Test receiveMoney()") {
        counter.receiveMoney(Currency(5, 0));
        REQUIRE(counter.getMoney() == Currency(15, 0));
    }

    SECTION("Test assignEmployee()") {
        std::unique_ptr<Employee> employee = std::make_unique<Employee>("Eliza", "Monroe");
        counter.assignEmployee(std::move(employee));
        REQUIRE(counter.getAssignedEmployee() == "Eliza Monroe");
    }

    SECTION("Test addClient() and getNumberOfClients()") {
        std::unique_ptr<Client> client1 = std::make_unique<Client>("Marta", "Ortega");
        std::unique_ptr<Client> client2 = std::make_unique<Client>("George", "Lazur");
        counter.addClient(std::move(client1));
        counter.addClient(std::move(client2));
        REQUIRE(counter.getNumberOfClients() == 2);
    }

    SECTION("Test serveFirstClient()") {
        std::unique_ptr<Client> client1 = std::make_unique<Client>("Kirin", "Smith");
        std::unique_ptr<Client> client2 = std::make_unique<Client>("Jack",  "Black");
        std::ofstream outputFile("test.txt");
        counter.addClient(std::move(client1));
        counter.addClient(std::move(client2));
        counter.serveFirstClient(outputFile);
        REQUIRE(counter.getNumberOfClients() == 1);
        REQUIRE(counter.getMoney() > Currency(0, 0));
    }
}
