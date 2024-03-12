#include "Prices.h"


//This is the constructor for the Prices class. It sets the initial prices of the goods.
Prices::Prices(std::string goods[], int goodslength) {
	for (int i = 0; i < goodslength; i++) {
		goodPrices[goods[i]] = 1;
	}
}

//This function gets the price of the goods the Pop will sell or buy.
double Prices::getPrice(std::string good) {
	return goodPrices[good];
}

//This function sets the price of the goods the Pop will sell or buy.
void Prices::setPrice(std::string good, double price) {
	goodPrices[good] = price;
}

//This function returns the map of the prices of the goods.
std::map<std::string, double>* Prices::getPrices() {
	return &goodPrices;
}
