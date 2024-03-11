#include <list>
#include <iostream>
#include "Order.h"

class Simulation {

private:
	std::list<Pop*> people;
	std::list<Depot*> depots;
	std::list<Order*> sellOrders;
	std::list<Order*> buyOrders;

public:
	void addBuyOrder(int quantity, std::string good, Pop* owner);
	void addSellOrder(int quantity, std::string good, Pop* owner);
	Pop* createNewPop(std::string popID, std::string caste, int money, Depot* setWorkLoc);
	Depot* createNewDepot(std::string goodProduced);
	void runTick();

};