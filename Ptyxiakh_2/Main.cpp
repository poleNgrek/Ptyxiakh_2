#include "Simulation.h"

#include "General_events.h"

#include <iostream>

int main()
{
    Simulation sim;

    std::cout << "Press 's' to start running the simulation.\n";
    char c;
    std::cin >> c;

    sim.schedule_event(Events::SIM_START);

    return 0;
}
