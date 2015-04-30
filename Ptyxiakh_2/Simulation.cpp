#include "Simulation.h"
#include "General_states.h"
#include "General_events.h"

#include <iostream>
#include <cstdlib>

/******************************************************************************/

// Simulation

// Constructor
// Initializes state classes and starts the first state.
Simulation::Simulation() : 
    simulation_start(*this),
    simulation_running(*this),
    simulation_exit(*this),
    m_current_state(nullptr),
    m_previous_state(States::ILLEGAL),
    m_current_event(Events::ILLEGAL)
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
}

void Simulation_exit::on_exit()
{
    std::cout << "Simulation_exit on_exit()\n";
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
