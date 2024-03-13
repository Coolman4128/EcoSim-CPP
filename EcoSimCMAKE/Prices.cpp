#include "Prices.h"


//This is the constructor for the Prices class. It sets the initial prices of the goods.
Prices::Prices(std::string goods[], int goodslength) {
	for (int i = 0; i < goodslength; i++) {
		goodPrices[goods[i]] = 5;
		priceHistory[goods[i]][0] = 5;
		priceHistory[goods[i]][1] = 1;
	}
}

//This function gets the price of the goods the Pop will sell or buy.
double Prices::getPrice(std::string good) {
	return goodPrices[good];
}

//This function sets the price of the goods the Pop will sell or buy.
void Prices::setPrice(std::string good, double price) {
	goodPrices[good] = price;
	priceHistory[good][0] = priceHistory[good][0] + price;
	priceHistory[good][1] = priceHistory[good][1] + 1;
}

//This function returns the map of the prices of the goods.
std::map<std::string, double>* Prices::getPrices() {
	return &goodPrices;
}

//This function updates the average price of the goods.
void Prices::updatePriceAverage(std::string good) {
	averagePrices[good] = priceHistory[good][0] / priceHistory[good][1];
	priceHistory[good][0] = averagePrices[good];
	priceHistory[good][1] = 1;
}

//This function returns the average price of the goods.
double Prices::getAveragePrice(std::string good) {
	return averagePrices[good];
}