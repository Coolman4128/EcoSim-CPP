#include "Pop.h"
#define COST 1
#define PRODUCTION 2

//This is the list of goods that the simulation will use. This can be expanded to include more goods.
std::string GOODS[] = { "food", "coal" };
std::string NEEDS[] = { "food", "coal" };
int SIZE_OF_GOODS = 2;
int SIZE_OF_NEEDS = 2;

//This function returns the unique ID of the Pop.
std::string Pop::getPopID() {
	return popID;
}


//This function returns the caste of the Pop.
std::string Pop::getPopCaste() {
	return caste;
}

//This is the constructor for the Pop class. It takes a unique ID, a caste, an amount of money, a pointer to the simulation, and a pointer to the work location.
Pop::Pop(std::string popID1, std::string caste1, double money1, Simulation* simPoint, Depot* setWorkLoc) {
	popID = popID1;
	caste = caste1;
	money = money1;
	popSim = simPoint;
	workLoc = setWorkLoc;
	fed = true;
	for(int i = 0; i < SIZE_OF_GOODS; i++) {
		popNeeds[GOODS[i]] = 0;
	}
	for (int i = 0; i < SIZE_OF_GOODS; i++) {
		goodsOwned[GOODS[i]] = 0;
	};
	for (int i = 0; i < SIZE_OF_GOODS; i++) {
		goodPrices[GOODS[i]] = 1;
	};
}

//This function returns the production efficiency of the Pop. This is used to determine how much of a good the Pop will produce when it works.
int Pop::getProductionEfficiency() {
	if (caste == "poor") {
		return 1 * PRODUCTION;
	}
	else if (caste == "middle") {
		return 2 * PRODUCTION;
	}
	else if (caste == "rich") {
		return 3 * PRODUCTION;
	}
	else {
		return 0;
	}
}

//This function makes the Pop work. It adds XXX units of the good produced by the work location to the Pop's inventory.
void Pop::work() { 
	if (fed == false) {
		return;
	}
	Depot placeOfWork = *workLoc;
	std::string goodProduced = placeOfWork.getGoodProduced();
	goodsOwned[goodProduced] = goodsOwned[goodProduced] + getProductionEfficiency();
	updateDailyNeeds();
}

//This function returns the amount of money the Pop has.
double Pop::getMoney() {
	return money;
}



//This function gets the price of the goods the Pop will sell or buy.
double Pop::getPrice(std::string good) {
	return goodPrices[good];
}

//This function sets the price of the goods the Pop will sell or buy.
void Pop::setPrice(std::string good, double price) {
	goodPrices[good] = price;
}

//This function provides the needs of the Pop. It checks if the Pop has enough of each good to satisfy its needs, satifies what it can and then updates the needs accordingly. 
int Pop::provideNeeds() {
	std::map<std::string, int>::iterator it;
	for (auto it = popNeeds.begin(); it != popNeeds.end(); ++it)
	{
		//if the pop has enough of the good to satisfy its needs, it does so and updates the needs accordingly, then sells the excess.
		if (goodsOwned[it->first] >= it->second) {
			goodsOwned[it->first] = goodsOwned[it->first] - it->second;
			popNeeds[it->first] = 0;
			sellGood(it->first, goodsOwned[it->first], getPrice(it->first));
			continue;
		}
		//if the pop has no need for the good, it does nothing.
		else if(it->second == 0) {
			continue;
		}
		//if the pop has some of the good, but not enough to satisfy its needs, it sells what it has and buys the rest.
		else {
			popNeeds[it->first] = popNeeds[it->first] - goodsOwned[it->first];
			if (money >= getPrice(it->first) * popNeeds[it->first]) {
				buyGood(it->first, popNeeds[it->first], getPrice(it->first));
			}
			continue;
		}
	}
	return 1;
}

bool Pop::getFed() {
	return fed;
}

void Pop::setFed(bool fed1) {
	fed = fed1;
}

//This function tells if the Pop has any needs.
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

//This function adds a good to the Pop's inventory.
void Pop::addGoods(std::string goodToAdd, int quantity) {
	goodsOwned[goodToAdd] = goodsOwned[goodToAdd] + quantity;
}

//This function puts a sell order in for a good.
int Pop::sellGood(std::string good, int quantity, double minPrice) {
	if (goodsOwned[good] < quantity) {
		return -1;
	}
	sellOrders.insert(sellOrders.begin(), new Order(quantity, good, minPrice, this));
	goodsOwned[good] = goodsOwned[good] - quantity;
	return 1;
}

//This function puts a buy order in for a good.
int Pop::buyGood(std::string good, int quantity, double maxPrice) {
	if (money < (quantity * maxPrice)) {
		return -1;
	}
	buyOrders.insert(buyOrders.begin(), new Order(quantity, good, maxPrice, this));
	money = money - quantity * maxPrice;
	return 1;
}

std::vector<Order*>* Pop::getSellOrders() {
	return &sellOrders;
}

std::vector<Order*>* Pop::getBuyOrders() {
	return &buyOrders;
}

//This function updates the Pop's needs.
void Pop::updateDailyNeeds(){
	for (int i = 0; i < SIZE_OF_NEEDS; i++) {
		popNeeds[NEEDS[i]] = popNeeds[NEEDS[i]] + 1;
	}
}

//This function adds money to the Pop's inventory.
void Pop::addMoney(double moneytoAdd) {
	money = money + moneytoAdd;
}