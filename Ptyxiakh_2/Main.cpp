#include "Simulation.h"

#include "General_events.h"

#include <iostream>

//#include "Functions.h"

#include <thread>
#include <future>
#include <chrono>

bool check_message(Simulation& sim);
void wait_for_input(Simulation& sim);

int main()
{
    Simulation sim;

    bool flag = false;

    std::future<void> input = std::async(std::launch::async,
        wait_for_input, std::ref(sim));

    while (!flag) // Infinite loop
    {
        flag = check_message(sim);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    input.get();

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

void wait_for_input(Simulation& sim)
{
    char s;
    std::cin >> s;
    if (s == 'e')
    {
        sim.set_event(Events::SIM_END);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}