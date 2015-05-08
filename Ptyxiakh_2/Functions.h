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
#include "Externals.h"

#include <future>
#include <vector>

class Simulation;
class Dispatcher;
class Core;

void populate_dispatchers(std::vector<Dispatcher>& vDisp);
void populate_cores(std::vector<Core>& vCore);
std::future<void> simulation_event_generator(Simulation& sim);
bool check_message(Simulation& sim);

#endif
