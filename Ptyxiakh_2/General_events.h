/**
  * General_events.h
  *
  * Here are stored the enumerated class events for the simulation, the cores
  * and the dispatchers.
  *
  * Version 0.5
  * Last edit: 11/09/2015
  *
  * K. Triantafyllou
  * B. Paleologos
  *
**/

#ifndef GENERAL_EVENTS_H_
#define GENERAL_EVENTS_H_

enum class Events
{
    SIM_START,
    SIM_STOP,
    SIM_END,
    DISP_JOB,
    DISP_IDLE,
    CORE_TOPOLOGY,
    CORE_JOB
};

#endif