#include <iostream>
#include "Pop.h"

class Order {
private:
	int quantity;
	std::string good;
	Pop* owner;

public:
	int getQuantity();
	void setQuantity(int newQuantity);
	std::string getGood();
	Pop* getOwner();
	Order(int quantity, std::string good, Pop* owner);
};