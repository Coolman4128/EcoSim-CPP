#include "Simulation.h"
#include <iostream>

//This is the list of goods that the simulation will use. This can be expanded to include more goods.
std::string GOODS1[] = { "food", "coal" };
std::string NEEDS1[] = { "food", "coal" };
int SIZE_OF_GOODS1 = 2;
int SIZE_OF_NEEDS1 = 2;


//This function creates a new Pop and adds it to the list of people in the simulation. It returns a pointer to the new Pop.
Pop* Simulation::createNewPop(std::string popID, std::string caste, double money, Depot* setWorkLoc) {
	Pop* createdPop = new Pop(popID, caste, money, this, setWorkLoc, this->goodPrices);
	people.insert(people.begin(), createdPop);
	return createdPop;
}

Simulation::Simulation() {
	for (int i = 0; i < SIZE_OF_GOODS1; i++) {
		goodSupply[GOODS1[i]] =	1;
		goodDemand[GOODS1[i]] = 1;
	};
	goodPrices = new Prices(GOODS1, SIZE_OF_GOODS1);
	tickCounter = 0;
}

//This function creates a new Depot and adds it to the list of depots in the simulation. It returns a pointer to the new Depot.
Depot* Simulation::createNewDepot(std::string goodProduced) {
	Depot* createdDepot = new Depot(goodProduced);
	depots.insert(depots.begin(), createdDepot);
	return createdDepot;
}

//This function adds all the buy orders from the Pops to the list of buy orders in the simulation.
void Simulation::addBuyOrders() {
	std::vector<Pop*>::iterator popIt;
	for (auto popIt = people.begin(); popIt != people.end(); ++popIt) {
		Pop* currentPop = (*popIt);
		buyOrders.insert(buyOrders.begin(), currentPop->getBuyOrders()->begin(), currentPop->getBuyOrders()->end());
		currentPop->getBuyOrders()->clear();
	}
}

//This function adds all the sell orders from the Pops to the vector of sell orders in the simulation.
void Simulation::addSellOrders() {
	std::vector<Pop*>::iterator popIt;
	for (auto popIt = people.begin(); popIt != people.end(); ++popIt) {  
		Pop* currentPop = (*popIt);
		sellOrders.insert(sellOrders.begin(), currentPop->getSellOrders()->begin(), currentPop->getSellOrders()->end());
		currentPop->getSellOrders()->clear();
	}
}

void Simulation::randomizePopOrder() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::shuffle(people.begin(), people.end(), e);
}

//This is the main function of the simulation. It advances the simulation one "tick" which is an abritrary unit of time, and the smallest.
//All the Pops wun through their tasks, sell/buy goods, take care of needs, etc.

void Simulation::runTick() {
	std::vector<Pop*>::iterator popIt;
	std::vector<Order*>::iterator sellIt;
	std::vector<Order*>::iterator buyIt;
	tickCounter++;
	if (tickCounter % 10 == 0) {
		for (int i = 0; i < SIZE_OF_GOODS1; i++) {
			goodPrices->updatePriceAverage(GOODS1[i]);
		};
	}
	randomizePopOrder();
	updateSimPrices();
	printPopWealth();
	printPopCount();

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
	findSupplyDemand();
	fillOrders();
	returnOrders();

	for (auto popIt = people.begin(); popIt != people.end(); ++popIt) {
		Pop* currentPop = (*popIt);
		currentPop->provideNeeds();
	}
	returnOrders();



	killStarvingPops(); 

}


void Simulation::killStarvingPops() { //this function is set up in a way that can be changed to kill the poops, but for now it just sets them to unfed.
	auto it = people.begin();
	while (it != people.end()) {
		if ((*it)->checkNeeds() != true) {
			(*it)->setFed(false);
			++it;
		}
		else {
			(*it)->setFed(true);
			++it;  // go to next
		}
	}

}

//This function prints how much money each Pop has.
void Simulation::printPopWealth() {
	std::vector<Pop*>::iterator popIt;
	for (auto popIt = people.begin(); popIt != people.end(); ++popIt) {
		Pop* currentPop = (*popIt);
		std::cout << currentPop->getPopID() << ": " << currentPop->getMoney() << std::endl;
	}
}

//This function prints how many pops are in the simulation.
void Simulation::printPopCount() {
	std::cout << people.size() << std::endl;
}

void Simulation::printOrderCount(){
	std::cout << buyOrders.size() << std::endl;
	std::cout << sellOrders.size() << std::endl;
}

void Simulation::findSupplyDemand() {
	std::vector<Order*>::iterator sellIt;
	std::vector<Order*>::iterator buyIt;
	std::map<std::string, double>::iterator goodIt;
	for (auto goodIt = goodSupply.begin(); goodIt != goodSupply.end(); ++goodIt) {
		goodSupply[goodIt->first] = 0;
		for (auto sellIt = sellOrders.begin(); sellIt != sellOrders.end(); ++sellIt) {
			Order* currentSellOrder = (*sellIt);
			if (currentSellOrder->getGood() == goodIt->first) {
				goodSupply[goodIt->first] = goodSupply[goodIt->first] + currentSellOrder->getQuantity();
			}
		}
	}
	for (auto goodIt = goodDemand.begin(); goodIt != goodDemand.end(); ++goodIt) {
		goodDemand[goodIt->first] = 0;
		for (auto buyIt = buyOrders.begin(); buyIt != buyOrders.end(); ++buyIt) {
			Order* currentBuyOrder = (*buyIt);
			if (currentBuyOrder->getGood() == goodIt->first) {
				goodDemand[goodIt->first] = goodDemand[goodIt->first] + currentBuyOrder->getQuantity();
			}
		}
	}
}


//This function runs through the orders and trys to fill as many as possible. It removes the orders that are filled from the vector of orders.
int Simulation::fillOrders() {
	std::vector<Order*>::iterator sellIt;
	std::vector<Order*>::iterator buyIt;

	for (auto sellIt = sellOrders.begin(); sellIt != sellOrders.end(); ++sellIt) {
		Order* currentSellOrder = (*sellIt);
		for (auto buyIt = buyOrders.begin(); buyIt != buyOrders.end(); ++buyIt) {
			Order* currentBuyOrder = (*buyIt);
			
			if (currentBuyOrder->getQuantity() == 0) {
				continue;
			}
			else if (currentSellOrder->getQuantity() == 0) {
				break;
			}
			else if (currentSellOrder->getGood() == currentBuyOrder->getGood() && currentSellOrder->getQuantity() >= currentBuyOrder->getQuantity()) {
				currentBuyOrder->getOwner()->addGoods(currentSellOrder->getGood(), currentBuyOrder->getQuantity());
				currentSellOrder->getOwner()->addMoney(currentBuyOrder->getQuantity() * currentBuyOrder->getPrice());
				currentSellOrder->setQuantity(currentSellOrder->getQuantity() - currentBuyOrder->getQuantity());
				std::cout << currentSellOrder->getOwner()->getPopID() << "sold " << currentBuyOrder->getQuantity() << " " << currentBuyOrder->getGood() << " to " << currentBuyOrder->getOwner()->getPopID() << " for " << currentBuyOrder->getPrice() << std::endl;
				currentBuyOrder->setQuantity(0);
				continue;
			}
			else if (currentSellOrder->getGood() == currentBuyOrder->getGood() && currentSellOrder->getQuantity() < currentBuyOrder->getQuantity()) {
				currentBuyOrder->getOwner()->addGoods(currentSellOrder->getGood(), currentSellOrder->getQuantity());
				currentSellOrder->getOwner()->addMoney(currentSellOrder->getQuantity() * currentBuyOrder->getPrice());
				currentBuyOrder->setQuantity(currentBuyOrder->getQuantity() - currentSellOrder->getQuantity());
				std::cout << currentSellOrder->getOwner()->getPopID() << "sold " << currentBuyOrder->getQuantity() << " " << currentBuyOrder->getGood() << " to " << currentBuyOrder->getOwner()->getPopID() << " for " << currentBuyOrder->getPrice() << std::endl;
				currentSellOrder->setQuantity(0);
				break;
			}
			else {
				continue;
			}
		}
	}
	return 0;
}

//This function returns all the orders that were not filled to the Pops that made them.
int Simulation::returnOrders() {
	std::vector<Order*>::iterator sellIt;
	std::vector<Order*>::iterator buyIt;
	Order* currentBuyOrder = NULL;
	Order* currentSellOrder = NULL;
	for (auto sellIt = sellOrders.begin(); sellIt != sellOrders.end(); ++sellIt) {
		currentSellOrder = *(sellIt);
		currentSellOrder->getOwner()->addGoods(currentSellOrder->getGood(), currentSellOrder->getQuantity());
		delete currentSellOrder;
	}
	sellOrders.clear();
	for (auto buyIt = buyOrders.begin(); buyIt != buyOrders.end(); ++buyIt) {
		currentBuyOrder = *(buyIt);
		currentBuyOrder->getOwner()->addMoney(currentBuyOrder->getQuantity() * currentBuyOrder->getPrice());
		delete currentBuyOrder;
	}
	buyOrders.clear();
	return 0;
}

void Simulation::updateSimPrices() {
	std::map<std::string, double>::iterator it;
	for (auto it = goodPrices->getPrices()->begin(); it != goodPrices->getPrices()->end(); ++it) {
		std::cout << goodDemand[it->first] << std::endl;
		std::cout << goodSupply[it->first] << std::endl;
		std::cout << "coefficent is " << (goodDemand[it->first] + 1.0) / (goodSupply[it->first] + 1.0) << std::endl;
		goodPrices->setPrice(it->first , (goodPrices->getPrice(it->first) * ((goodDemand[it->first] + 1.0) /(goodSupply[it->first] + 1.0))));
	}

}

