#include <iostream>
#include <map>
#include <vector>
#include "Depot.h"
#include "Prices.h"
#include "Order.h"
#include "Needs.h"

class Simulation;


//This class represents a person in the simulation. It has a unique ID, a caste, a work location, money, needs, goods owned, and buy/sell orders.
class Pop {
private:
	std::string popID;
	std::string caste;
	Depot* workLoc;
	double money;
	Needs* popNeeds;
	std::map<std::string, int> goodsOwned;
	std::vector<Order*> sellOrders;
	std::vector<Order*> buyOrders;
	Simulation* popSim;
	Prices* goodPrices;
	bool dying;
	bool fed;

public:
	Pop(std::string popID, std::string caste, double money, Simulation* sim, Depot* setWorkLoc, Prices* simPrice);
	std::string getPopID();
	std::string getPopCaste();
	double getMoney();
	void work();
	int provideNeeds();
	bool checkNeeds();
	void makeBuyDecision();
	void makeSellDecision();
	double getDayNeedsCost();
	void addGoods(std::string goodToAdd, int quantity);
	int sellGood(std::string good, int quantity, double minPrice);
	int buyGood(std::string good, int quantity, double maxPrice);
	std::vector<Order*>* getSellOrders();
	std::vector<Order*>* getBuyOrders();
	void updateDailyNeeds();
	void addMoney(double moneyToAdd);
	int getProductionEfficiency();
	bool getFed();
	void setFed(bool fed);
	void setDying(bool dying);
	bool getDying();
	Depot* getWorkLoc();
};


