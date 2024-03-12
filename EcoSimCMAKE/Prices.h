#include <map>
#include <string>
#include <iostream>

class Prices {
private:
	std::map<std::string, double> goodPrices;

public:
	Prices(std::string goods[], int goodslength);
	void setPrice(std::string good, double price);
	double getPrice(std::string good);
	std::map<std::string, double>* getPrices();
};