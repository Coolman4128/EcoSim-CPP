// EcoSimCMAKE.cpp : Defines the entry point for the application.
//
#include <string>
#include "EcoSimCMAKE.h"
#include "Simulation.h"
int main()
{
	Simulation sim1;
	Depot* cool = sim1.createNewDepot("food");
	Depot* cool2 = sim1.createNewDepot("coal");


	for (int i = 0; i < 10; i++) {
		sim1.createNewPop("tyler" + std::to_string(i), "poor", 300.00, cool);
	}
	for (int i = 0; i < 10; i++) {
		sim1.createNewPop("lindsey" + std::to_string(i), "poor", 300.00, cool2);
	}
	for (int i = 0; i < 20; i++) {
		sim1.createNewPop("luke" + std::to_string(i), "middle", 300.00, cool);
	}
	for (int i = 0; i < 20; i++) {
		sim1.createNewPop("lauren" + std::to_string(i), "middle", 300.00, cool2);
	}
	for (int i = 0; i < 500; i++) {
		sim1.runTick();
	}

	return 0;
}
