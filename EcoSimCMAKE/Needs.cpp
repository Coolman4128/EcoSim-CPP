#include "Needs.h"

std::string NEEDS2[] = { "food", "coal" };
int SIZE_OF_NEEDS2 = 2;

Needs::Needs(std::string needType) {
	this->needType = needType;
	for (int i = 0; i < SIZE_OF_NEEDS2; i++) {
		popNeeds[NEEDS2[i]] = 1;
	}
}

void Needs::setNeeds(std::string need, int value) {
	popNeeds[need] = value;
}

int Needs::getNeeds(std::string need) {
	return popNeeds[need];
}

bool Needs::checkNeeds() {
	std::map<std::string, int>::iterator it;
	for (auto it = popNeeds.begin(); it != popNeeds.end(); ++it) {
		if (it->second == 0) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

std::map<std::string, int>* Needs::getNeedsMap() {
	return &popNeeds;
}
