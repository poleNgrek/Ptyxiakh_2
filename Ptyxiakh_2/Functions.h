/**
  * Functions.h
  *
  * Holds functions of varying tasks that do not fit in anywhere else
  *
  * Version 0.1
  * Last edit: 21/04/2015
  *
  * K. Triantafyllou
  * B. Paleologos
  *
**/

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <future>

class Simulation;

std::future<void> simulation_event_generator(Simulation& sim);
bool check_message(Simulation& sim);

#endif