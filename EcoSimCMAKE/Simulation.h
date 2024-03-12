#include <vector>
#include <iostream>
#include "Pop.h"
#include <algorithm>   
#include <vector>       
#include <random>      
#include <chrono>

//This class is the main class of the simulation. It contains all the Pops, Depots, and Orders, and runs the simulation.
class Simulation {

private:
	std::vector<Pop*> people;
	std::vector<Depot*> depots;
	std::vector<Order*> sellOrders;
	std::vector<Order*> buyOrders;
	int fillOrders();
	int returnOrders();
	Prices* goodPrices;
	std::map<std::string, double> goodSupply;
	std::map<std::string, double> goodDemand;

public:
	Simulation();
	void addBuyOrders();
	void addSellOrders();
	Pop* createNewPop(std::string popID, std::string caste, double money, Depot* setWorkLoc);
	Depot* createNewDepot(std::string goodProduced);
	void runTick();
	void printPopWealth();
	void printPopCount();
	void printOrderCount();
	void killStarvingPops();
	void randomizePopOrder();
	void updatePopPrices();
	void updateSimPrices();
	double getGoodSupply(std::string good);
	double getGoodDemand(std::string good);
	void findSupplyDemand();

};