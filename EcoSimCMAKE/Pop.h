#include <iostream>
#include <map>
#include "Depot.h"

class Simulation;

class Pop {
private:
	std::string popID;
	std::string caste;
	Depot* workLoc;
	int money;
	std::map<std::string, int> popNeeds;
	std::map<std::string, int> goodsOwned;
	Simulation* popSim;

public:
	Pop(std::string popID, std::string caste, int money, Simulation* sim, Depot* setWorkLoc);
	std::string getPopID();
	std::string getPopCaste();
	void work();
	int provideNeeds();
	bool checkNeeds();
	void addGoods(std::string goodToAdd, int quantity);
	void sellGood(std::string good, int quantity);
	void buyGood(std::string good, int quantity);
};


