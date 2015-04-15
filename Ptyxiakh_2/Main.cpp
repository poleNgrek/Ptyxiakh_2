#include "Simulation.h"

#include "General_events.h"

#include <iostream>

bool check_message(Simulation& sim);

int main()
{
    Simulation sim;

    bool flag = false;

    while (!flag) // Infinite loop
    {
        flag = check_message(sim);
    }

    return 0;
}

bool check_message(Simulation& sim)
{
    if (sim.get_event() == Events::SIM_END)
    {
        return true;
    }
    return false;
}