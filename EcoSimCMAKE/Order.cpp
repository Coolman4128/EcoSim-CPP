#include "Order.h"

Order::Order(int quan, std::string goo, Pop* setOwner) {
	quantity = quan;
	good = goo;
	owner = setOwner;
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