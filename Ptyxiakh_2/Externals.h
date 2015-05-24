#ifndef EXTERNALS_H_
#define EXTERNALS_H_

#include <vector>
#include <memory>
#include <random>
#include <chrono>
#include <functional>

class Dispatcher;
class Core;

using namespace std;

extern vector<unique_ptr<Dispatcher>> vDisp;
extern vector<unique_ptr<Core>> vCore;

extern auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();


#endif // EXTERNALS_H_
