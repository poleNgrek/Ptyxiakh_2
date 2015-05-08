#include "Functions.h"
#include "Externals.h"
#include "Simulation.h"
#include "General_events.h"

#include <iostream>

#include <thread>
#include <mutex>
#include <chrono>

class Dispatcher;

void wait_for_input(Simulation& sim);

std::future<void> simulation_event_generator(Simulation& sim)
{
    std::future<void> input = std::async(std::launch::async,
                                         wait_for_input, std::ref(sim));
    return input;
}

void wait_for_input(Simulation& sim)
{
    char s = 'i';
    std::mutex m;
    std::unique_lock<std::mutex> guard_cout(m, std::defer_lock);
    while (s != 'e')
    {
        guard_cout.lock();
        if (std::cin >> s)
        {
            switch (s)
            {
                case 'r':
                    sim.schedule_event(Events::SIM_START);
                    break;
                case 's':
                    sim.schedule_event(Events::SIM_STOP);
                    break;
                case 'e':
                    sim.schedule_event(Events::SIM_END);
                    break;
                default:
                    break;
            }
        }
        else
        {
            std::this_thread::yield();
        }
        guard_cout.unlock();
    }
}

bool check_message(Simulation& sim)
{
    if (sim.get_event() == Events::SIM_END)
    {
        return true;
    }
    return false;
}

void populate_dispatchers()
{
    std::cout << "Enter your desired number of Dispatchers:\n";
    std::cout << "> ";
    int dispNumb;
    std::cin >> dispNumb;

    /// Make room for desired Dispatchers
    vDisp.reserve(dispNumb);

    /// Create the actual Dispatchers
    for (auto i=0; i<dispNumb; ++i){
        vDisp.push_back(std::unique_ptr<Dispatcher> (new Dispatcher));
        std::cout<<"Disp n."<<i<<" Created"<<std::endl;
}
}

void populate_cores()
{
    std::cout << "Enter your desired number of Cores:\n";
    std::cout << "> ";
    int coreNumb;
    std::cin >> coreNumb;

    /// Make room for desired Core
    vCore.reserve(coreNumb);

    /// Create the actual Dispatchers
    for (auto i=0; i<coreNumb; ++i)
    {
        vCore.push_back(std::unique_ptr<Core> (new Core));
        //vCore.at(i).id=i;
       // std::cout<<"Fake ID for core: "<<vCore.at(i).id<<" (Inside function/populate_cores)\n";
    }
}
