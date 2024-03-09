// EcoSimCMAKE.cpp : Defines the entry point for the application.
//

#include "EcoSimCMAKE.h"
#include "Simulation.h"
int main()
{
	std::cout << "Hello CMake." << std::endl;
	Simulation cool;
	std::cout << cool.cool(8);
	return 0;
}
