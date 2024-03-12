#include "Order.h"

Order::Order(int quan, std::string goo, int setPrice, Pop* setOwner) {
	quantity = quan;
	good = goo;
	owner = setOwner;
	price = setPrice;
}

int Order::getQuantity() {
	return quantity;
}
std::string Order::getGood() {
	return good;
}
void Order::setQuantity(int newQuantity) {
	quantity = newQuantity;
}

Pop* Order::getOwner() {
	return owner;
}

int Order::getPrice() {
	return price;
}