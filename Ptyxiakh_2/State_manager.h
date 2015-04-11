/**
  * State_manager.h
  *
  * Templated abstract manager for the handling of states across various state
  * machines.
  *
  * Version 1.2
  * Last edit: 11/04/2015
  *
  * K. Triantafyllou
  * B. Paleologos
  *
**/

#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_

// Forward declarations
enum class States;
enum class Events;

// Template declaration. A state machine can be anything that uses states.
template <class State_machine>
class State_manager
{
public:
    // Constructor
    State_manager(States state_id, State_machine& state_machine_controller) :
        m_state_id(state_id),
        m_state_machine_controller(state_machine_controller)
    {
    }

    // Virtual destructor
    virtual ~State_manager()
    {
    }

    // We don't want to change the state from here.
    const States get_state() const
    {
        return m_state_id;
    }

    // These functions need to be overriden by the inheriting class
    virtual void on_entry() = 0;
    virtual void on_exit() = 0;
    virtual void handle_event(Events) = 0;

    /*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
    // Deleted constructors and functions
    State_manager() = delete;
    State_manager(const State_manager&) = delete;
    State_manager& operator=(const State_manager&) = delete;
    /*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
protected:
    States m_state_id;
    State_machine& m_state_machine_controller; // Inherited state machines can
                                               // use the State_manager
};

#endif
