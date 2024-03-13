#include "Pop.h"
#define COST 1
#define PRODUCTION 2
#define AVERAGE_COEFFICIENT 1
#define SELLAVERAGECO 1
#define MONEY_COEFFICIENT 1.1

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
Pop::Pop(std::string popID1, std::string caste1, double money1, Simulation* simPoint, Depot* setWorkLoc, Prices* simPrice) {
	popID = popID1;
	caste = caste1;
	money = money1;
	popSim = simPoint;
	workLoc = setWorkLoc;
	fed = true;
	dying = false;
	popNeeds = new Needs("life");
	for (int i = 0; i < SIZE_OF_GOODS; i++) {
		goodsOwned[GOODS[i]] = 0;
	};
	goodPrices = simPrice;
}

Depot* Pop::getWorkLoc() {
	return workLoc;
}

//This function checks if the Pop has enough of each good to satisfy its needs. If it does, it returns true. If it does not, it returns false.
bool Pop::checkNeeds() {
	return popNeeds->checkNeeds();
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
		return 5 * PRODUCTION;
	}
	else {
		return 0;
	}
}

void Pop::setDying(bool dying1) {
	dying = dying1;
}

bool Pop::getDying() {
	return dying;
}

//This function makes the Pop work. It adds XXX units of the good produced by the work location to the Pop's inventory.
void Pop::work() { 
	if (fed == false) {
		Depot placeOfWork = *workLoc;
		std::string goodProduced = placeOfWork.getGoodProduced();
		goodsOwned[goodProduced] = goodsOwned[goodProduced] + (getProductionEfficiency()/2);
		updateDailyNeeds();
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

//This function provides the needs of the Pop. It checks if the Pop has enough of each good to satisfy its needs, satifies what it can and then updates the needs accordingly. 
int Pop::provideNeeds() {
	std::map<std::string, int>::iterator it;
	for (auto it = popNeeds->getNeedsMap()->begin(); it != popNeeds->getNeedsMap()->end(); ++it)
	{
		//if the pop has enough of the good to satisfy its needs, it does so and updates the needs accordingly.
		if (goodsOwned[it->first] >= it->second) {
			goodsOwned[it->first] = goodsOwned[it->first] - it->second;
			popNeeds->setNeeds(it->first, 0);
			continue;
		}
		//if the pop has no need for the good, it does nothing.	
		else if(it->second == 0) {
			continue;
		}
		//if the pop has some of the good, but not enough to satisfy its needs, it fullfills what it can.
		else {
			popNeeds->setNeeds(it->first, popNeeds->getNeeds(it->first) - goodsOwned[it->first]);
			continue;
		}
	}
	return 1;
}

//This function makes a decision on what goods to buy. There are many conditions that would cause a pop to buy goods.
void Pop::makeBuyDecision() {

	//If the pop has enough money to buy all the goods it needs, it will do so.
	if (money >= getDayNeedsCost()) {
		for (int i = 0; i < SIZE_OF_GOODS; i++) {
			if (popNeeds->getNeeds(GOODS[i]) > 0) {
				buyGood(GOODS[i], popNeeds->getNeeds(GOODS[i]), goodPrices->getPrice(GOODS[i]));
			}
		}
	}
	else {
		//Buy as many goods as the pop can afford
		for (int i = 0; i < SIZE_OF_GOODS; i++) {
			if (popNeeds->getNeeds(GOODS[i]) > 0 && money > (popNeeds->getNeeds(GOODS[i]) * goodPrices->getPrice(GOODS[i]))) {
				buyGood(GOODS[i], popNeeds->getNeeds(GOODS[i]), goodPrices->getPrice(GOODS[i]));
			}
		}
		//Prevent pops with little money from wasting it by returning before the next conditions.
		return;
	}
	//If the pop has enough money to buy all the goods it needs, it will then look for goods that are below the average price that it needs and can afford and buys them.
	bool noMoney = false;
	while (!noMoney) {
		for (int i = 0; i < SIZE_OF_GOODS; i++) {
		std::string* needFinder = std::find(NEEDS, NEEDS + SIZE_OF_NEEDS, GOODS[i]);
		bool goodIsNeeded = needFinder != NEEDS + SIZE_OF_NEEDS;
			if (goodIsNeeded && (money > getDayNeedsCost() || goodPrices->getPrice(GOODS[i]) < (goodPrices->getAveragePrice(GOODS[i]) * AVERAGE_COEFFICIENT)) && money >= goodPrices->getPrice(GOODS[i]) * MONEY_COEFFICIENT) {
				buyGood(GOODS[i], 1, goodPrices->getPrice(GOODS[i]));
			}
			else {
				noMoney = true;
			}
		}
	}
}

void Pop::makeSellDecision() {
	//If the pop isnt fed, or there is a good with a higher than average price then it will sell any extra it has. 
	for (int i = 0; i < SIZE_OF_GOODS; i++) {
		if (popNeeds->getNeeds(GOODS[i]) == 0 && goodsOwned[GOODS[i]] > 0 && (money <= getDayNeedsCost()*2 || goodPrices->getPrice(GOODS[i]) > goodPrices->getAveragePrice(GOODS[i]) * SELLAVERAGECO)) {
			//CHANGE hoy many goods to sell to either be 1 or how ever many will pay for tommorows needs. 
			int goodsToSell = 0;
			if (!fed) {
				goodsToSell = goodsOwned[GOODS[i]];
			}
			else if (goodsOwned[GOODS[i]] > 1) {
				goodsToSell = 2;
			}
			else {
				goodsToSell = 1;
			}
			sellGood(GOODS[i], goodsToSell, goodPrices->getPrice(GOODS[i]));
		}
	}
}
bool Pop::getFed() {
	return fed;
}

void Pop::setFed(bool fed1) {
	fed = fed1;
}

double Pop::getDayNeedsCost() {
	double cost = 0;
	if (popNeeds->checkNeeds() == true) {
		return 0;
	}
	std::map<std::string, int>::iterator it;
	for (auto it = popNeeds->getNeedsMap()->begin(); it != popNeeds->getNeedsMap()->end(); ++it)
	{
		if (it->second > 0) {
			cost = cost + (it->second * goodPrices->getPrice(it->first));
		}
	}
	return cost;
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
		popNeeds->setNeeds(NEEDS[i], popNeeds->getNeeds(NEEDS[i]) + 1);
	}
}

//This function adds money to the Pop's inventory.
void Pop::addMoney(double moneytoAdd) {
	money = money + moneytoAdd;
}