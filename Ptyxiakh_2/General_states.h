/**
  * General_states.h
  *
  * Here are stored the general states of the simulation, the cores and the
  * dispatchers. The header file also provides a C-style array to hold the names
  * of the enums and a function to return that name.
  *
  * Version 0.9
  * Last edit: 11/04/2015
  *
  * K. Triantafyllou
  * B. Paleologos
  *
**/

#ifndef GENERAL_STATES_H_
#define GENERAL_STATES_H_

enum class States
{
    ILLEGAL,
    SIM_START,
    SIM_RUN,
    SIM_END,
    DISP_IDLE,
    DISP_SERVE,
    CORE_TOPOLOGY,
    CORE_IDLE,
    CORE_SERVE
};

// Simple C-style array with C-strings as names for the enums.
static const char* state_string[] =
{
    "ILLEGAL", "SIM_START", "SIM_RUN", "SIM_END", "DISP_IDLE", "DISP_SERVE",
    "CORE_TOPOLOGY", "CORE_IDLE", "CORE_SERVE"
};

// Simple function that takes a States enum class and returns the C-style array.
// Note: enum class cannot be implicitly converted to int, thus a static_cast
// is needed.
const char* state_to_text(States state)
{
    return state_string[static_cast<int>(state)];
}

#endif