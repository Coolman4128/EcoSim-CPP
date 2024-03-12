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


	for (int i = 0; i < 300; i++) {
		sim1.createNewPop("tyler" + std::to_string(i), "worker", 3, cool);
	}
	for (int i = 0; i < 100; i++) {
		sim1.createNewPop("lindsey" + std::to_string(i), "worker", 3, cool2);
	}
	for (int i = 0; i < 5000; i++) {
		sim1.runTick();
	}

	return 0;
}
