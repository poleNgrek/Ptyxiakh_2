/**
  * General_events.h
  *
  * Here are stored the enumerated class events for the simulation, the cores
  * and the dispatchers. The header file also provides a C-style array to hold
  * the names of the enums and a function to return that name.
  *
  * Version 0.9.1
  * Last edit: 15/04/2015
  *
  * K. Triantafyllou
  * B. Paleologos
  *
**/

#ifndef GENERAL_EVENTS_H_
#define GENERAL_EVENTS_H_

enum class Events
{
    ILLEGAL,
    SIM_START,
    SIM_STOP,
    SIM_END,
    DISP_JOB,
    DISP_IDLE,
    CORE_IDLE,
    CORE_TOPOLOGY,
    CORE_JOB
};

// Simple C-style array with C-strings as names for the enums.
static const char* event_string[] =
{
    "ILLEGAL", "SIM_START", "SIM_STOP", "SIM_END", "DISP_JOB", "DISP_IDLE",
    "CORE_IDLE", "CORE_TOPOLOGY", "CORE_JOB"
};

// Simple function that takes a Events enum class and returns the C-style array.
// Note: enum class cannot be implicitly converted to int, thus a static_cast
// is needed.
static const char* event_to_text(Events events)
{
    return event_string[static_cast<int>(events)];
}

#endif
