#include <iostream>

class Pop;

class Order {
private:
	int quantity;
	double price;
	std::string good;
	Pop* owner;

public:
	int getQuantity();
	double getPrice();
	void setQuantity(int newQuantity);
	std::string getGood();
	Pop* getOwner();
	Order(int quantity, std::string good, double price, Pop* owner);
};