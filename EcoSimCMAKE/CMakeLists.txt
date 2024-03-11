# CMakeList.txt : CMake project for EcoSimCMAKE, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (EcoSimCMAKE "EcoSimCMAKE.cpp" "EcoSimCMAKE.h" "Simulation.h" "Simulation.cpp" "Pop.h" "Pop.cpp" "Order.cpp" "Depot.h" "Depot.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET EcoSimCMAKE PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
