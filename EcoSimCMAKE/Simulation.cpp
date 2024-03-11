#include "Simulation.h"
#include <iostream>



//This function creates a new Pop and adds it to the list of people in the simulation. It returns a pointer to the new Pop.
Pop* Simulation::createNewPop(std::string popID, std::string caste, int money, Depot* setWorkLoc) {
	Pop* createdPop = new Pop(popID, caste, money, this, setWorkLoc);
	people.insert(people.begin(), createdPop);
	return createdPop;
}

//This function creates a new Depot and adds it to the list of depots in the simulation. It returns a pointer to the new Depot.
Depot* Simulation::createNewDepot(std::string goodProduced) {
	Depot* createdDepot = new Depot(goodProduced);
	depots.insert(depots.begin(), createdDepot);
	return createdDepot;
}

//This function adds all the buy orders from the Pops to the list of buy orders in the simulation.
void Simulation::addBuyOrders() {
	std::list<Pop*>::iterator popIt;
	for (auto popIt = people.begin(); popIt != people.end(); ++popIt) {
		Pop* currentPop = (*popIt);
		buyOrders.insert(buyOrders.begin(), currentPop->getBuyOrders()->begin(), currentPop->getBuyOrders()->end());
		currentPop->getBuyOrders()->clear();
	}
	std::cout << buyOrders.size();
}

//This function adds all the sell orders from the Pops to the list of sell orders in the simulation.
void Simulation::addSellOrders() {
	std::list<Pop*>::iterator popIt;
	for (auto popIt = people.begin(); popIt != people.end(); ++popIt) {  
		Pop* currentPop = (*popIt);
		sellOrders.insert(sellOrders.begin(), currentPop->getSellOrders()->begin(), currentPop->getSellOrders()->end());
		currentPop->getSellOrders()->clear();
	}
	std::cout << sellOrders.size();
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

	addBuyOrders();
	addSellOrders();

}

