/**
  * Simulation.h
  *
  * General simulation of the environment needed to run the algorithms. It pro-
  * vides an interface for the actual states and manages them through the
  * State_manager abstract class.
  * The states have each their own logic and are implemented as separate classes
  * friended with the main class Simulation.
  * Each state has an on_entry and an on_exit function, as well as an event 
  * handler (handle_event), which are inherited from the State_manager class.
  * These functions need to be overriden.
  *
  * Version 0.8
  * Last edit: 15/04/2015
  *
  * K. Triantafyllou
  * B. Paleologos
  *
**/

#ifndef SIMULATION_H_
#define SIMULATION_H_

// Necessary includes
#include "State_manager.h"

// Forward declarations
enum class States;
enum class Events;

class Simulation;

/******************************************************************************/
// States of Simulation
// State Start
class Simulation_start : public State_manager<Simulation>
{
public:
    Simulation_start(Simulation&);

    void on_entry() override;
    void on_exit() override;
    void handle_event(Events) override;
};

// State Running
class Simulation_running : public State_manager<Simulation>
{
public:
    Simulation_running(Simulation&);

    void on_entry() override;
    void on_exit() override;
    void handle_event(Events) override;
};

// State Exit
class Simulation_exit : public State_manager<Simulation>
{
public:
    Simulation_exit(Simulation&);

    void on_entry() override;
    void on_exit() override;
    void handle_event(Events) override;
};
/******************************************************************************/

/******************************************************************************/
// State manager class
class Simulation
{
public:
    // Constructor
    Simulation();
    // Destructor
    ~Simulation();

    // Takes and event and processes it
    void schedule_event(Events);

    // Static so it can be run only once
    static void initialization();

    // Event getter
    Events get_event();

    /*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
    // Deleted constructors and functions
    Simulation(const Simulation&) = delete;
    Simulation& operator=(const Simulation&) = delete;
    /*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
private:
    // Friended state classes
    friend class Simulation_start;
    friend class Simulation_running;
    friend class Simulation_exit;

    // States declarations
    Simulation_start simulation_start;
    Simulation_running simulation_running;
    Simulation_exit simulation_exit;

    // Current and previous state
    State_manager<Simulation>* m_current_state;
    States m_previous_state;
    // Current event being handled
    Events m_current_event;

    // Goes to a new state
    void change_state(States);
    // Event setter
    void set_event(Events);
};
/******************************************************************************/

#endif
