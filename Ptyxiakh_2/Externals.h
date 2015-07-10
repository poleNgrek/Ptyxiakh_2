/**
  * Externals.h
  *
  * Version 0.5
  * Last edit: 10/07/2015
  *
  * Variables wich will be used across the whole project
  *
  * K. Triantafyllou
  * B. Paleologos
  *
**/

#ifndef EXTERNALS_H_
#define EXTERNALS_H_

#include <vector>
#include <memory>

// Forward declaration
class Dispatcher;
class Core;

/// Vector of pointers to dispatcher objects
extern std::vector<std::unique_ptr<Dispatcher>> vDisp;
/// Vector of pointers to core objects
extern std::vector<std::unique_ptr<Core>> vCore;

/// Seed for random functions
extern int seed;

#endif // EXTERNALS_H_
