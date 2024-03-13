// EcoSimCMAKE.cpp : Defines the entry point for the application.
//
#include <string>
#include "EcoSimCMAKE.h"
#include "Simulation.h"
#include <fstream>

#define PATH "C:/Users/Tyler Watson/source/repos/EcoSimCMAKE/dataout/popInfo.csv"

int main()
{
	Simulation sim1;
	Depot* cool = sim1.createNewDepot("food");
	Depot* cool2 = sim1.createNewDepot("coal");


	for (int i = 0; i < 50; i++) {
		sim1.createNewPop("tyler" + std::to_string(i), "poor", 30.00, cool);
	}
	for (int i = 0; i < 50; i++) {
		sim1.createNewPop("lindsey" + std::to_string(i), "poor", 30.00, cool2);
	}/*
	for (int i = 0; i < 20; i++) {
		sim1.createNewPop("luke" + std::to_string(i), "middle", 30.00, cool);
	}
	for (int i = 0; i < 20; i++) {
		sim1.createNewPop("lauren" + std::to_string(i), "middle", 30.00, cool2);
	}
	*/
	for (int i = 0; i < 3; i++) {
		sim1.runTick();
		std::ofstream popInfoFile;
		popInfoFile.open(PATH, std::ios::in | std::ios::out | std::ios::trunc);
		std::cout << popInfoFile.is_open() << "poop";
		if (popInfoFile.is_open()) {
			popInfoFile << sim1.getPopInfo();
			popInfoFile.close();
		}
	}

	return 0;
}
