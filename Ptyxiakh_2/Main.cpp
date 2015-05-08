#include "Simulation.h"
#include "Dispatcher.h"
#include "Core.h"
#include "Functions.h"
#include "Externals.h"

#include <vector>
#include <iostream>

class Dispatcher;
class Core;

std::vector<Dispatcher> vDisp;
std::vector<Core> vCore;

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

