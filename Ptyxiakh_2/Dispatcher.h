/**
Header file includes basic set up such as:
    a)simple constructor and private queues
    b)classes for handling states
    c)functions for handling queues (names self-explanatory)
        1)get_job_q
        2)get_core_q
        3)add_job_q
        4)add_core_q
        5)pop_job_q
        6)pop_core_q
    d)functions that extend dispatcher's functionality such as
        1)schedule_event
        2)assign_job (to a core)
        3)fill_core_queue

**/

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "State_manager.h"
#include <queue>
#include "Core.h"

using namespace std;

enum class States;
enum class Events;

class Dispatcher;
//class Core; // so we can use Core class inside Dispacher functions

class Dispatcher_serve : public State_manager<Dispatcher>
{
public:
    Dispatcher_serve(Dispatcher&);

    void on_entry();
    void on_exit();
    void handle_event(Events);

};

class Dispatcher_idle : public State_manager<Dispatcher>
{
public:
    Dispatcher_idle(Dispatcher&);

    void on_entry();
    void on_exit();
    void handle_event(Events);

};

/*class Dispacher_exit: public State_manager<Dispacher>
{
    public:
        Dispacher_exit(Dispacher&);

        void on_entry();
        void on_exit();
        void handle_event(Events);
}*/

class Dispatcher
{
public:
    Dispatcher();
    ~Dispatcher();

    void schedule_event(Events);
    void assign_job(int job);
    // Event setter
    void set_event(Events);

    // Event getter
    Events get_event();
    //void fill_core_queue();

    /* Getters for dispatcher queues */

    int get_job_q()
    {
        return disp_job_queue.front();
    }

    Core& get_core_q()
    {
        return disp_core_queue.front();
    }

    /*Adders-Setters for dispatcher queues */

    void add_job_q(int job)
    {
        disp_job_queue.push(job);
    }

    void add_core_q(Core& core)
    {
        disp_core_queue.push(core);
    }

    /*pop functions*/

    void pop_job_q()
    {
        disp_job_queue.pop();
    }

    void pop_core_q()
    {
        disp_core_queue.pop();
    }

private:
    queue<int> disp_job_queue;//queue for incoming random numbers
    queue<Core> disp_core_queue; // somehow it should include core handlers

    friend class Dispatcher_serve;
    friend class Dispatcher_idle;
    //friend class Dispacher_exit;

    Dispatcher_serve disp_state_serve;
    Dispatcher_idle disp_state_idle;
    //Dispacher_exit disp_state_exit;

    State_manager<Dispatcher>* disp_curr_state;
    States disp_prev_state;
    Events disp_current_event;

    void change_state(States);
};

#endif
