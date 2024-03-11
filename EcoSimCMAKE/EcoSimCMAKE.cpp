// EcoSimCMAKE.cpp : Defines the entry point for the application.
//

#include "EcoSimCMAKE.h"
#include "Simulation.h"
int main()
{
	Simulation sim1;
	Depot* cool = sim1.createNewDepot("food");
	Pop* tylerPoint = sim1.createNewPop("tyler", "worker", 100, cool);
	Pop* tylerPoint2 = sim1.createNewPop("tyler2", "worker", 100, cool);
	return 0;
}
