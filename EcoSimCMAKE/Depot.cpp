#include "Depot.h"

Depot::Depot(std::string setGoodProduced) {
	goodProduced = setGoodProduced;
}

std::string Depot::getGoodProduced() {
	return goodProduced;
}