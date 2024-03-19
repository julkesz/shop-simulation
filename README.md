# Shop simulation
Simulation of a regular store written in C++.

## Description

C++ program to simulate actions typical for regular stores: entering the shop by clients, choosing and buying products. In the shop, several employees work (let's assume we're dealing with a small shop). Customers enter and leave the shop, spending a certain number of time units inside. The goods in the shop are divided into categories, which determine the rate of VAT. Customers can freely choose the goods they want to buy. A cashier calculates the payment, accepts the payment, and issues a receipt to the customer.

The main part of the program, further referred to as the simulation, is divided into 3 phases, where the instructions of each phase are executed at least once for each iteration. Before the main iterations are executed, a list of the employees is generated randomly, and then they are assigned to specific counters previously loaded from the file. Then, the user is informed about the start of the main part of the simulation. One iteration of the simulation consists of the following phases:

1. The first step of the phase is to randomly select the number of customers entering the store (from 0 to 3 customers). The next step is to create customers, giving them random names and surnames, as well as the amount of money they enter the store with. Then, it is determined how many products each customer wants to buy.

2. In this phase, customers who entered the store select specific products. In one iteration, each customer chooses only one product (this is done by random selection). This process continues until the customer reaches the desired number of products or until the customer runs out of money. In this phase, customers who finish selecting products also line up at a counter depending on the number of people standing in each queue (after selecting products, the customer goes to the counter with the smallest number of people waiting).

3. This phase contains instructions for serving customers at the counter. The customer's purchases are added together (checking if the customer has not exceeded the budget), then the customer gives a specified amount of money, which goes into the cash register. In one iteration, only the first customers from all queues are served.

The program has the following characteristics:
- It is an **object-oriented** system that makes use of inheritance and polymorphism.
- **STL** vectors, maps, queues are used to properly store data.
- Some level of **randomness** is applied to generate number of employees, clients and products they choose.
- Unit tests are written using **Catch2** library.


## Running the application
To run the program, run the executable file located in main directory:
```
./ShopSimulation
```
The information needed to start the simulation is stored in /data directory. When the simulation is completed, its output is written to /data/output_file.txt.
