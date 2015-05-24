#include "Core.h"
#include "Dispatcher.h"
#include "General_states.h"
#include "General_events.h"
#include "Functions.h"
#include "Externals.h"

#include <iostream>
#include <cstdlib>

class Dispatcher;

Core::Core() :
	core_state_topology(*this),
	core_state_idle(*this),
	core_state_serve(*this),
	core_curr_state(nullptr),
	core_prev_state(States::ILLEGAL)
	{
		change_state(States::CORE_TOPOLOGY);
	}

Core::~Core()
{
	if(core_curr_state)
	{
		core_curr_state->on_exit();
	}

	core_curr_state = nullptr;
}

void Core::schedule_event(Events event)
{
	core_curr_state->handle_event(event);
	set_event(event);
}

void Core::set_event(Events events)
{
    core_curr_event = events;
}

Events Core::get_event()
{
    return core_curr_event;
}

void Core::change_state(States new_state)
{
	//COPY PASTAAAAAAAAA

	if(core_curr_state)
	{
		core_curr_state->on_exit();
		core_prev_state = core_curr_state->get_state();
	}

	switch(new_state)
	{
		case States::CORE_TOPOLOGY:
			core_curr_state = &core_state_topology;
			break;
		case States::CORE_IDLE:
			core_curr_state = &core_state_idle;
			break;
		case States::CORE_SERVE:
			core_curr_state = &core_state_serve;
			break;
		default:
			core_curr_state = nullptr;
			std::cout << "Illegal state transition!\n"
            << "Our previous state was "
            << state_to_text(core_prev_state)
            << " and the new state was "
            << state_to_text(new_state)
            << std::endl;
			exit(-15);
			break;
	}
	core_curr_state->on_entry();
}


int Core::fill_core_queue()
{
    int dispatchR;

    if(!is_inside_disp()){
       dispatchR = random_disp();//getting random dispatcher
       vDisp.at(dispatchR)->add_core_q(*this);
       it_is_now();//inside the core_queue of a random disp hopefully
    }

    return dispatchR;
}

/* STATE CLASSES CONSTRUCTORS WITH THEIR FUNCTIONS ON_ENTRY/ON_EXIT */

// // // // // // // // // // // // // // // // // // // // // // // // // // //

						//CORE_TOPOLOGY
Core_topology::Core_topology(Core& state_controller)
	: State_manager(States::CORE_TOPOLOGY, state_controller)
	{}

void Core_topology::on_entry()
{
	std::cout<<"Dis iz Core_topology on_entry IN DA HOYSE"<<std::endl;
	int dsptcher = m_state_machine_controller.fill_core_queue();
	std::cout<<"I joined successfully disp No. "<<dsptcher<<std::endl;
}

void Core_topology::on_exit()
{
	std::cout<<"Diz iz Core_topology on_exit"<<std::endl;
}

void Core_topology::handle_event(Events event)
{
	switch(event)
	{
		case Events::CORE_IDLE:
			m_state_machine_controller.change_state(States::CORE_IDLE);
			break;
		case Events::CORE_JOB:
			m_state_machine_controller.change_state(States::CORE_SERVE);
		default:
			break;
	}
}

/* ************************************************************ */

// // // // // // // // // // // // // // // // // // // // // // // // // // //

						//CORE_IDLE
Core_idle::Core_idle(Core& state_controller)
	: State_manager(States::CORE_IDLE, state_controller)
	{}

void Core_idle::on_entry()
{
	std::cout<<"Dis iz Core_idle on_entry IN DA HOYSE"<<std::endl;
}

void Core_idle::on_exit()
{
	std::cout<<"Diz iz Core_idle on_exit"<<std::endl;
}

void Core_idle::handle_event(Events event)
{
	switch(event)
	{
		case Events::CORE_TOPOLOGY:
			m_state_machine_controller.change_state(States::CORE_TOPOLOGY);
			break;
		case Events::CORE_JOB:
			m_state_machine_controller.change_state(States::CORE_SERVE);
		default:
			break;
	}
}

/* ************************************************************ */

// // // // // // // // // // // // // // // // // // // // // // // // // // //

						//CORE_SERVE
Core_serve::Core_serve(Core& state_controller)
	: State_manager(States::CORE_SERVE, state_controller)
	{}

void Core_serve::on_entry()
{
	std::cout<<"Dis iz Core_serve on_entry IN DA HOYSE"<<std::endl;
}

void Core_serve::on_exit()
{
	std::cout<<"Diz iz Core_serve on_exit"<<std::endl;
}

void Core_serve::handle_event(Events event)
{
	switch(event)
	{
		case Events::CORE_IDLE:
			m_state_machine_controller.change_state(States::CORE_IDLE);
			break;
		case Events::CORE_TOPOLOGY:
			m_state_machine_controller.change_state(States::CORE_TOPOLOGY);
		default:
			break;
	}
}

/* ************************************************************ */
