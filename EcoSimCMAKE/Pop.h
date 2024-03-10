#include <iostream>
#include <map>
class Pop {
private:
	std::string popID;
	std::string caste;
	int workLoc;
	int money;
	std::map<std::string, int> popNeeds;

public:
	std::string getPopID();
	std::string getPopCaste();
	void work();
	int provideNeeds();
	void sellGood(std::string good, int quantity);
	void buyGood(std::string good, int quantity);
};


