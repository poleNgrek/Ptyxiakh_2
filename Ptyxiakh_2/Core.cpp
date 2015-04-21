#include "Core.h"
#include "General_states.h"
#include "General_events.h"

#include <iostream>

Core::Core() :
	core_state_topology(*this),
	core_state_idle(*this),
	core_state_serve(*this),
	core_curr_state(nullptr),
	core_prev_state(STATES::ILLEGAL)
	{
		change_state(STATES::CORE_TOPOLOGY);
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
}

void change_state(States new_state)
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
            << state_to_text(m_previous_state)
            << " and the new state was "
            << state_to_text(new_state)
            << std::endl;
			exit(-15);
			break;
	}
	core_curr_state->on_entry();
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

						//CORE_TOPOLOGY
Core_topology::Core_topology(Core& state_controller)
	: State_manager(States::CORE_TOPOLOGY, state_controller)
	{}
	
void Core_topology::on_entry()
{
	std::cout<<"Dis iz Core_topology on_entry IN DA HOYSE"<<std::endl;
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
			m_state_machine_controller.change_state(States::CORE_SERVE)
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
			m_state_machine_controller.change_state(States::CORE_SERVE)
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
			m_state_machine_controller.change_state(States::CORE_TOPOLOGY)
		default:
			break;
	}
}
	
/* ************************************************************ */