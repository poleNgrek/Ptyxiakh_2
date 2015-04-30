#include "Dispacher.h"
#include "Core.h"
#include "General_states.h"
#include "General_events.h"
//#include "Externals.h"

#include <iostream>
#include <cstdlib>

using namespace std;

Dispacher::Dispacher() :
	disp_state_serve(*this),
	disp_state_idle(*this),
	disp_curr_state(nullptr),
	disp_prev_state(States::ILLEGAL)
{
	change_state(States::DISP_IDLE);
}

Dispacher::~Dispacher()
{
	if(disp_curr_state)
	{
		disp_curr_state->on_exit();
	}

	disp_curr_state = nullptr;
}

void Dispacher::schedule_event(Events event)
{
	disp_curr_state->handle_event(event);
}

//CORES should NOT be able to get a job while inside topology state
//we assume topology state as a set up state where cores join dispatchers' queues
void Dispacher::assign_job(int job)
{
	//getting the first core from dispacher's core_queue.
	Core& kor = get_core_q();

	//popping the core we got from the dispacher's queue.
	pop_core_q();

	//Assigning the job - Changing the the state where needed

	if(kor.get_event() == Events::CORE_IDLE)
	{
		kor.schedule_event(Events::CORE_JOB);
		kor.add_core_job_q(job);
	}
	else if(kor.get_event() == Events::CORE_JOB)
	{
		kor.add_core_job_q(job);
	}
	else{
		cout<<"Error, Core is not ready to get the job."<<endl;
	}
}

void Dispacher::fill_core_queue()
{

}

void Dispacher::change_state(States new_state)
{
	//copy-pasta from charlie's awesome error checking
	if (disp_curr_state)
    {
        // First we make sure to cleanup the state we are in
        disp_curr_state->on_exit();
        // Then we can safely set our previous state variable
        disp_prev_state = disp_curr_state->get_state();
    }

    switch (new_state)
    {
    case States::DISP_IDLE:
        disp_curr_state = &disp_state_idle;
        break;
    case States::DISP_SERVE:
        disp_curr_state = &disp_state_serve;
        break;
    default:
        // First set our current state to nothing.
        disp_curr_state = nullptr;
        // Print out error message
        std::cout << "Illegal state transition!\n"
            << "Our previous state was "
            << state_to_text(disp_prev_state)
            << " and the new state was "
            << state_to_text(new_state)
            << std::endl;
			exit(-15);
			break;
    }

    // If all is OK, we can start the new state.
    disp_curr_state->on_entry();
}

/* STATE CLASSES CONSTRUCTORS WITH THEIR FUNCTIONS ON_ENTRY/ON_EXIT */

						//DISPACHER_IDLE
Dispacher_idle::Dispacher_idle(Dispacher& state_controller)
	: State_manager(States::DISP_IDLE, state_controller)
	{}

void Dispacher_idle::on_entry()
{
	std::cout << "This is Dispacher_idle on_entry"<<std::endl;
}

void Dispacher_idle::on_exit()
{
	std::cout<<"This is Dispacher_idle on_exit"<<std::endl;
}

void Dispacher_idle::handle_event(Events event)
{
	switch(event)
	{
		case Events::DISP_JOB:
			m_state_machine_controller.change_state(States::DISP_SERVE);
			break;
		default:
			break;
	}
}


// // // // // // // // // // // // // // // // // // // // // // // // // // //

						//DISPACHER_SERVE
Dispacher_serve::Dispacher_serve(Dispacher& state_controller)
	: State_manager(States::DISP_SERVE, state_controller)
	{}

void Dispacher_serve::on_entry()
{
	std::cout<<"Dis iz Dispacher_serve on_entry IN DA HOYSE"<<std::endl;


}

void Dispacher_serve::on_exit()
{
	std::cout<<"Diz iz Dispacher_serve on_exit"<<std::endl;
}

void Dispacher_serve::handle_event(Events event)
{
	switch(event)
	{
		case Events::DISP_IDLE:
			m_state_machine_controller.change_state(States::DISP_IDLE);
			break;
		default:
			break;
	}
}

/* ************************************************************ */
