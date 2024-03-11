#include <list>
#include <iostream>
#include "Pop.h"


//This class is the main class of the simulation. It contains all the Pops, Depots, and Orders, and runs the simulation.
class Simulation {

private:
	std::list<Pop*> people;
	std::list<Depot*> depots;
	std::list<Order*> sellOrders;
	std::list<Order*> buyOrders;

public:
	void addBuyOrders();
	void addSellOrders();
	Pop* createNewPop(std::string popID, std::string caste, int money, Depot* setWorkLoc);
	Depot* createNewDepot(std::string goodProduced);
	void runTick();

};