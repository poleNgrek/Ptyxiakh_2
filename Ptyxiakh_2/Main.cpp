#include "Simulation.h"
#include "Dispatcher.h"
#include "Core.h"
#include "Functions.h"
#include "Externals.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

class Dispatcher;
class Core;

using namespace std;

vector<std::unique_ptr<Dispatcher>> vDisp;
vector<std::unique_ptr<Core>> vCore;

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Simulation sim;
    bool flag = false;

    ////////////////////////////////
    int sth = random_disp();
    cout<<sth<<" random disp"<<endl;
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
        worker_thread.get();
    }

    worker_thread.get();

    return 0;
}

