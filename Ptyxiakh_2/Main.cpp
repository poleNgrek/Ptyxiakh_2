#include "Simulation.h"
#include "Functions.h"

#include <iostream>

int main()
{
    Simulation sim;
    bool flag = false;

    std::cout <<
    "Enter 'r' to run\n" <<
    "'s' to stop\n" <<
    "'e' to exit.\n" <<
    " > ";

    auto worker_thread = simulation_event_generator(sim);

    while (!flag) // Infinite loop
    {
        flag = check_message(sim);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    worker_thread.get();

    return 0;
}
