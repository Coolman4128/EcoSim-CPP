#include <iostream>
#include <map>
#include <vector>
#include "Depot.h"
#include "Order.h"

class Simulation;


//This class represents a person in the simulation. It has a unique ID, a caste, a work location, money, needs, goods owned, and buy/sell orders.
class Pop {
private:
	std::string popID;
	std::string caste;
	Depot* workLoc;
	int money;
	std::map<std::string, int> popNeeds;
	std::map<std::string, int> goodsOwned;
	std::vector<Order*> sellOrders;
	std::vector<Order*> buyOrders;
	Simulation* popSim;

public:
	Pop(std::string popID, std::string caste, int money, Simulation* sim, Depot* setWorkLoc);
	std::string getPopID();
	std::string getPopCaste();
	int getMoney();
	void work();
	int provideNeeds();
	bool checkNeeds();
	void addGoods(std::string goodToAdd, int quantity);
	int sellGood(std::string good, int quantity, int minPrice);
	int buyGood(std::string good, int quantity, int maxPrice);
	std::vector<Order*>* getSellOrders();
	std::vector<Order*>* getBuyOrders();
	void updateDailyNeeds();
	void addMoney(int moneyToAdd);
};


