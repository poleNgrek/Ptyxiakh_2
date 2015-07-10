#include "Simulation.h"
#include "Functions.h"
#include "Externals.h"

#include <iostream>
#include <chrono>
#include <functional>


class Dispatcher;
class Core;

// Not abusing "using namespace std"
// We use cout and cin since they are the most prevalent
using std::cout;
using std::cin;

std::vector<std::unique_ptr<Dispatcher>> vDisp;
std::vector<std::unique_ptr<Core>> vCore;

// Static_cast because we don't want 64bit numbers
int seed = static_cast<int>
    (std::chrono::high_resolution_clock::now().time_since_epoch().count());

int main()
{
    Simulation sim;
    bool flag = false;

    ////////////////////////////////
    int sth = random_disp();
    cout<< sth <<" random disp" <<endl;
    //////////////////////////////////

    cout <<
    "Enter\n'r' to run\n" <<
    "'s' to stop\n" <<
    "'e' to exit.\n" <<
    " > ";

    auto worker_thread = simulation_event_generator(sim);

    while (!flag) // Infinite loop
    {
        flag = check_message(sim);
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    worker_thread.get();

    return 0;
}
