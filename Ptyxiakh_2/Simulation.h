/**
  * Simulation.h
  *
  * General simulation of the environment needed to run the algorithms. The
  * states implemented are Start, Running, Exit
  *
  * Version 0.6
  * Last edit: 11/04/2015
  *
  * K. Triantafyllou
  * B. Paleologos
  *
**/

#ifndef SIMULATION_H_
#define SIMULATION_H_

// Forward declarations
enum class States;
enum class Events;
template <class State_machine>
class State_manager;

class Simulation
{
public:
    // Constructor
    Simulation();
    // Destructor
    ~Simulation();

    // Takes and event and processes it
    void schedule_event(Events);

    /*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
    // Deleted constructors and functions
    Simulation(const Simulation&) = delete;
    Simulation& operator=(const Simulation&) = delete;
    /*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
private:
    State_manager<Simulation>* m_current_state;
    States m_previous_state;

    // Goes to a new state
    void change_state(States);
    // Static so it can be run only once
    static void initialization();
};

#endif