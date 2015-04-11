#include <iostream> /// For screen I/O
#include <chrono>
#include <stdlib.h>
#include <thread>
#include <mutex>

using namespace std;
mutex mu;

void call_from_thread(int tid){
    mu.lock();
    cout<<"HELLO THREAD "<<tid<<" IS IN DA HOUSE"<<endl;
    mu.unlock();
}

static const int num_t = 10;

int main(){
    thread t[num_t];
     for (int y=0;y<num_t;y++){
        t[y] = thread(call_from_thread,y);
    }

    for(int z = 0;z<num_t;z++){
        t[z].join();
    }

    /*srand((unsigned)time(0));

    for(int i=0;i<50;i++){
   // srand((unsigned)time(0));
    unsigned int random_integer;
    int lowest = 0, highest = 100;
    int range = (highest - lowest) + 1;

    random_integer = lowest + int(range * rand() / (RAND_MAX + 1.0));

    cout<<random_integer<<endl;
    }

    thread t1{call_from_thread};
    t1.join();*/


    return 0;
}
