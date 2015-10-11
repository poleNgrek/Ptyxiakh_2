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

#include "Dispatcher.h"
#include "Core.h"

#include <future>
#include <vector>
#include <stdlib.h>

class Simulation;
class Dispatcher;
class Core;

void populate_dispatchers();
void populate_cores();
std::future<void> simulation_event_generator(Simulation& sim);
bool check_message(Simulation& sim);
std::future<void> sim_running_thread(Simulation& sim);
void w8_for_input(Simulation& sim);
bool check_me2(Simulation& sim);
int random_disp();
int random_core();

#endif
