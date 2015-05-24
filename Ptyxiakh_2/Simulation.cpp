#include "Simulation.h"
#include "General_states.h"
#include "General_events.h"
#include "Functions.h"
#include "Externals.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

/******************************************************************************/

//extern std::vector<Dispatcher> vDisp;
//extern std::vector<Core> vCore;

// Simulation

// Constructor
// Initializes state classes and starts the first state.
Simulation::Simulation() :
    simulation_start(*this),
    simulation_running(*this),
    simulation_exit(*this),
    m_current_state(nullptr),
    m_previous_state(States::ILLEGAL),
    m_current_event(Events::ILLEGAL),
    current_state(States::ILLEGAL)
{
    change_state(States::SIM_START);
}

// When Simulation is destroyed, we have to be sure to cleanup the state we are
// currently in. Then the current state can be safely set to nothing (nullptr).
Simulation::~Simulation()
{
    if (m_current_state)
    {
        m_current_state->on_exit();
    }
    m_current_state = nullptr;
}


// Uses the event handler of the current state.
void Simulation::schedule_event(Events events)
{
    // The function handle_event is defined in each event Simulation has.
    m_current_state->handle_event(events);
    set_event(events);
}

// Uses a basic switch statement to see what new state has been selected.
void Simulation::change_state(States new_state)
{
    if (m_current_state)
    {
        // First we make sure to cleanup the state we are in
        m_current_state->on_exit();
        // Then we can safely set our previous state variable
        m_previous_state = m_current_state->get_state();
    }

    switch (new_state)
    {
    case States::SIM_START:
        m_current_state = &simulation_start;
        break;
    case States::SIM_RUN:
        m_current_state = &simulation_running;
        break;
    case States::SIM_END:
        m_current_state = &simulation_exit;
        break;
    default:
        // First set our current state to nothing.
        m_current_state = nullptr;
        // Print out error message
        std::cout << "Illegal state transition!\n"
            << "Our previous state was "
            << state_to_text(m_previous_state)
            << " and the new state was "
            << state_to_text(new_state)
            << std::endl;
        exit(-15);
        break;
    }

    // If all is OK, we can start the new state.
    m_current_state->on_entry();
}

void Simulation::initialization()
{
    std::cout<<"Simulation on initialization !!"<<std::endl;
    populate_dispatchers();
    populate_cores();
}

void Simulation::set_event(Events events)
{
    m_current_event = events;
}

Events Simulation::get_event()
{
    return m_current_event;
}
/******************************************************************************/

/******************************************************************************/

// States of Simulation

// State Start
Simulation_start::Simulation_start(Simulation& state_controller)
    : State_manager(States::SIM_START, state_controller)
{
}

void Simulation_start::on_entry()
{
    std::cout << "Simulation_start on_entry()\n";
    if(vDisp.empty())
        {
        if(vCore.empty())
        {
            m_state_machine_controller.initialization();
        }
    }
}

void Simulation_start::on_exit()
{
    std::cout << "Simulation_start on_exit()\n";

}

void Simulation_start::handle_event(Events events)
{
    switch (events)
    {
    case Events::SIM_START:
        m_state_machine_controller.change_state(States::SIM_RUN);
        break;
    case Events::SIM_END:
        m_state_machine_controller.change_state(States::SIM_END);
        break;
    default:
        break;
    }
}

// State Running
Simulation_running::Simulation_running(Simulation& state_controller)
    : State_manager(States::SIM_RUN, state_controller)
{
}

void Simulation_running::on_entry()
{
    std::cout << "Simulation_running on_entry()\n";
    std::cout<<"State: "<<state_to_text(m_state_machine_controller.m_current_state->get_state())<<std::endl;
    bool flag = false;
    auto sim_run_thread = sim_running_thread(m_state_machine_controller);

    while (!flag) // Infinite loop producing random numbers every "poisson" time
    {
        flag = check_me2(m_state_machine_controller);
        std::cout<<"DA FAQ "<<flag<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    //sim_run_thread.get();


    //std::cout<<"State: "<<state_to_text(m_state_machine_controller.m_previous_state)<<std::endl;
}

void Simulation_running::on_exit()
{
    std::cout << "Simulation_running on_exit()\n";
}

void Simulation_running::handle_event(Events events)
{
    switch (events)
    {
    case Events::SIM_STOP:
        m_state_machine_controller.change_state(States::SIM_START);
        break;
    case Events::SIM_END:
        m_state_machine_controller.change_state(States::SIM_END);
        break;
    default:
        break;
    }
}

// State Exit
Simulation_exit::Simulation_exit(Simulation& state_controller)
    : State_manager(States::SIM_END, state_controller)
{
}

void Simulation_exit::on_entry()
{
    std::cout << "Simulation_exit on_entry()\n";

    /*if (!vCore.empty())
    {
        std::cout << "I need to destruct " << vCore.size() << " cores." << std::endl;
        vCore.clear();
        std::cout << vCore.size() << " remain" << std::endl;

    }*/

    if (!vDisp.empty())
    {
        std::cout<<"I need to destruct "<< vDisp.size() <<" disps."<<std::endl;
        vDisp.clear();
        std::cout<<vDisp.size()<<" remain"<<std::endl;
    }
}

void Simulation_exit::on_exit()
{
    std::cout << "Simulation_exit on_exit()\n";
    //std:exit(0);
}

void Simulation_exit::handle_event(Events events)
{
    /*switch (events)
    {
    case Events::SIM_STOP:
    m_state_machine_controller.change_state(States::SIM_START);
    break;
    case Events::SIM_END:
    m_state_machine_controller.change_state(States::SIM_END);
    break;
    default:
    break;
    }*/
}
/******************************************************************************/
