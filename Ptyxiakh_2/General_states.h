/**
  * General_states.h
  *
  * Here are stored the general states of the simulation, the cores and the
  * dispatchers
  *
  * Version 0.5
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

#endif