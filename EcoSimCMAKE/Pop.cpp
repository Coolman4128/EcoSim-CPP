#include "Pop.h"

std::string Pop::getPopID() {
	return popID;
}

std::string Pop::getPopCaste() {
	return caste;
}

Pop::Pop(std::string popID1, std::string caste1, int money1, Simulation* simPoint, Depot* setWorkLoc) {
	popID = popID1;
	caste = caste1;
	money = money1;
	popSim = simPoint;
	workLoc = setWorkLoc;
	popNeeds["food"] = 5;
	goodsOwned["food"] = 0;
}

void Pop::work() { 
	Depot placeOfWork = *workLoc;
	std::string goodProduced = placeOfWork.getGoodProduced();
	goodsOwned[goodProduced] = goodsOwned[goodProduced] + 3;
	std::cout << goodsOwned["food"];
}

int Pop::provideNeeds() {
	std::map<std::string, int>::iterator it;
	for (auto it = popNeeds.begin(); it != popNeeds.end(); ++it)
	{
		if (goodsOwned[it->first] > it->second) {
			goodsOwned[it->first] = goodsOwned[it->first] - it->second;
			popNeeds[it->first] = 0;
			continue;
		}
		else if(it->second == 0) {
			continue;
		}
		else {
			popNeeds[it->first] = popNeeds[it->first] - goodsOwned[it->first];
			goodsOwned[it->first] = 0;
			continue;
		}
	}
	std::cout << popNeeds["food"];
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