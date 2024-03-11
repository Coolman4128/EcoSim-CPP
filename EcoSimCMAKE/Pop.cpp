#include "Pop.h"
#define COST 1

//This function returns the unique ID of the Pop.
std::string Pop::getPopID() {
	return popID;
}


//This function returns the caste of the Pop.
std::string Pop::getPopCaste() {
	return caste;
}

//This is the constructor for the Pop class. It takes a unique ID, a caste, an amount of money, a pointer to the simulation, and a pointer to the work location.
Pop::Pop(std::string popID1, std::string caste1, int money1, Simulation* simPoint, Depot* setWorkLoc) {
	popID = popID1;
	caste = caste1;
	money = money1;
	popSim = simPoint;
	workLoc = setWorkLoc;
	popNeeds["food"] = 5;
	goodsOwned["food"] = 10;
}

//This function makes the Pop work. It adds XXX units of the good produced by the work location to the Pop's inventory.
void Pop::work() { 
	Depot placeOfWork = *workLoc;
	std::string goodProduced = placeOfWork.getGoodProduced();
	goodsOwned[goodProduced] = goodsOwned[goodProduced] + 3;
}


//This function provides the needs of the Pop. It checks if the Pop has enough of each good to satisfy its needs, satifies what it can and then updates the needs accordingly. 
int Pop::provideNeeds() {
	std::map<std::string, int>::iterator it;
	for (auto it = popNeeds.begin(); it != popNeeds.end(); ++it)
	{
		//if the pop has enough of the good to satisfy its needs, it does so and updates the needs accordingly, then sells the excess.
		if (goodsOwned[it->first] > it->second) {
			goodsOwned[it->first] = goodsOwned[it->first] - it->second;
			popNeeds[it->first] = 0;
			sellGood(it->first, goodsOwned[it->first], COST);
			goodsOwned[it->first] = 0;
			continue;
		}
		//if the pop has no need for the good, it does nothing.
		else if(it->second == 0) {
			continue;
		}
		//if the pop has some of the good, but not enough to satisfy its needs, it sells what it has and buys the rest.
		else {
			popNeeds[it->first] = popNeeds[it->first] - goodsOwned[it->first];
			goodsOwned[it->first] = 0;
			if (money > COST * popNeeds[it->first]) {
				buyGood(it->first, popNeeds[it->first], COST);
				money = money - (COST * popNeeds[it->first]);
			}
			continue;
		}
	}
	return 1;
}

bool Pop::checkNeeds() {
	std::map<std::string, int>::iterator it;
	for (auto it = popNeeds.begin(); it != popNeeds.end(); ++it) {
		if (it->second == 0) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

void Pop::addGoods(std::string goodToAdd, int quantity) {
	goodsOwned[goodToAdd] = goodsOwned[goodToAdd] + quantity;
}

int Pop::sellGood(std::string good, int quantity, int minPrice) {
	if (goodsOwned[good] < quantity) {
		return -1;
	}
	sellOrders.insert(sellOrders.begin(), new Order(quantity, good, minPrice, this));
	goodsOwned[good] = goodsOwned[good] - quantity;
	return 1;
}

int Pop::buyGood(std::string good, int quantity, int maxPrice) {
	if (money < (quantity * maxPrice)) {
		return -1;
	}
	buyOrders.insert(buyOrders.begin(), new Order(quantity, good, maxPrice, this));
	money = money - quantity;
	return 1;
}

std::list<Order*>* Pop::getSellOrders() {
	return &sellOrders;
}

std::list<Order*>* Pop::getBuyOrders() {
	return &buyOrders;
}