#include "Simulation.h"
#include "Dispatcher.h"
#include "Core.h"
#include "Functions.h"
#include "Externals.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

class Dispatcher;
class Core;

std::vector<std::unique_ptr<Dispatcher>> vDisp;
std::vector<std::unique_ptr<Core>> vCore;

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    Simulation sim;
    bool flag = false;
    int sth = random_disp();
    std::cout<<sth<<" random disp"<<std::endl;

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

