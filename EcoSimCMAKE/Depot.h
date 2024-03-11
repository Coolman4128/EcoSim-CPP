#include <iostream>

class Depot {
private:
	std::string goodProduced;


public:
	Depot(std::string goodProduced);
	std::string getGoodProduced();
};