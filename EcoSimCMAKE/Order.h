#include <iostream>

class Pop;

class Order {
private:
	int quantity;
	int price;
	std::string good;
	Pop* owner;

public:
	int getQuantity();
	int getPrice();
	void setQuantity(int newQuantity);
	std::string getGood();
	Pop* getOwner();
	Order(int quantity, std::string good, int price, Pop* owner);
};