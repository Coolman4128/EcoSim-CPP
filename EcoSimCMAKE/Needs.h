#include <map>
#include <string>
#include <iostream>

class Needs {
private:
	std::map<std::string, int> popNeeds;
	std::string needType;

public:
	Needs(std::string needType);
	void setNeeds(std::string need, int value);
	int getNeeds(std::string need);
	bool checkNeeds();
	std::map<std::string, int>* getNeedsMap();
};