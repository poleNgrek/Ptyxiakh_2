#include "Simulation.h"
#include "Functions.h"
#include "Externals.h"

#include <iostream>
#include <chrono>
#include <fstream>
#include <ctime>

// Not abusing "using namespace std"
// We use cout, cin and endl since they are the most prevalent
using std::cout;
using std::cin;
using std::endl;

// Forward declarations
class Dispatcher;
class Core;

// External definitions
std::vector<std::unique_ptr<Dispatcher> > vDisp;
std::vector<std::unique_ptr<Core> > vCore;
unsigned seed =
    std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);

int main()
{
    std::ofstream myfile("Logs.txt",std::ios::in|std::ios::out|std::ios::app);
    if(!myfile)
    {
        std::cerr << "Can't open output file 'Logs.txt'"<<std::endl;
        exit(EXIT_FAILURE);
    }
    if(myfile.is_open()){
        myfile << "\nLOG FILE BEGIN\n";
        myfile.close();
    }

    std::chrono::time_point<std::chrono::system_clock> start, fin;
    start = std::chrono::system_clock::now();

    Simulation sim;
    bool flag = false;

    ////////////////////////////////      //WTF
    int sth = random_disp();              //WTF
    cout<< sth <<" random disp" <<endl;   //WTF
    //////////////////////////////////    //WTF

    cout <<
         "Enter\n'r' to run\n" <<
         "'s' to stop\n" <<
         "'e' to exit.\n" <<
         " > ";

    auto worker_thread = simulation_event_generator(sim);

    while (!flag) // Infinite loop
    {
        flag = check_message(sim);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    worker_thread.get();

    fin = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = fin-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(fin);

    //std::ofstream myfile("Logs.txt",std::ios::in|std::ios::out|std::ios::app);
    if(!myfile)
    {
        std::cerr << "Can't open output file 'Logs.txt'"<<std::endl;
        exit(EXIT_FAILURE);
    }
    myfile.open("Logs.txt",std::ios::in|std::ios::out|std::ios::app);
    if(myfile.is_open()){
        myfile << "finished computation at " << std::ctime(&end_time)
               << "\nelapsed time: " << elapsed_seconds.count() << "s\n";
        myfile.close();
    }

    return 0;
}
