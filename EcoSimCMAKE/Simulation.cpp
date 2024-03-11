#include "Simulation.h"
#include <iostream>

Pop* Simulation::createNewPop(std::string popID, std::string caste, int money, Depot* setWorkLoc) {
	Pop* createdPop = new Pop(popID, caste, money, this, setWorkLoc);
	people.insert(people.begin(), createdPop);
	return createdPop;
}

Depot* Simulation::createNewDepot(std::string goodProduced) {
	Depot* createdDepot = new Depot(goodProduced);
	depots.insert(depots.begin(), createdDepot);
	return createdDepot;
}

void Simulation::addBuyOrder(int quantity, std::string good, Pop* owner) {
	Order* newOrder = new Order(quantity, good, owner);
	buyOrders.insert(buyOrders.begin(), newOrder);
}

void Simulation::addSellOrder(int quantity, std::string good, Pop* owner) {
	Order* newOrder = new Order(quantity, good, owner);
	sellOrders.insert(sellOrders.begin(), newOrder);
}


//This is the main function of the simulation. It advances the simulation one "tick" which is an abritrary unit of time, and the smallest.
//All the Pops wun through their tasks, sell/buy goods, take care of needs, etc.

void Simulation::runTick() {
	std::list<Pop*>::iterator popIt;
	std::list<Order*>::iterator sellIt;
	std::list<Order*>::iterator buyIt;
	for (auto popIt = people.begin(); popIt != people.end(); ++popIt) {
		Pop* currentPop = (*popIt);
		currentPop->work();
	}

	for (auto popIt = people.begin(); popIt != people.end(); ++popIt) {
		Pop* currentPop = (*popIt);
		currentPop->provideNeeds();
	}

}