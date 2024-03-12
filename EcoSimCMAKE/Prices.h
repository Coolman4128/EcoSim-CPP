#include <map>
#include <string>
#include <iostream>

class Prices {
private:
	std::map<std::string, double> goodPrices;
	std::map<std::string, double> averagePrices;
	std::map<std::string, double[2]> priceHistory;

public:
	Prices(std::string goods[], int goodslength);
	void setPrice(std::string good, double price);
	double getPrice(std::string good);
	std::map<std::string, double>* getPrices();
	void updatePriceAverage(std::string good);
	double getAveragePrice(std::string good);
};