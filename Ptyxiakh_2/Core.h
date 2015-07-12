#ifndef CORE_H_
#define CORE_H_

#include "State_manager.h"

#include <queue>

// Forward declarations
// Enumerators
enum class States;
enum class Events;
// Classes
class Core;
class Dispatcher;

/******************************************************************************/
// States of Core
// State Topology
class Core_topology : public State_manager<Core>
{
	public:
		Core_topology(Core&);

		void on_entry();
		void on_exit();
		void handle_event(Events);
};

// State Idle
class Core_idle : public State_manager<Core>
{
	public:
		Core_idle(Core&);

		void on_entry();
		void on_exit();
		void handle_event(Events);
};

// State Serve
class Core_serve : public State_manager<Core>
{
	public:
		Core_serve(Core&);

		void on_entry();
		void on_exit();
		void handle_event(Events);
};
/******************************************************************************/

/******************************************************************************/
// Core class
class Core
{
	public:
        // Constructor
		Core();
        // Destructor
		~Core();

        // Takes and event and processes it
		void schedule_event(Events);

        // Event getter
		Events get_event();

		int fill_core_queue();

		int get_core_job_q()
        {
            return core_job_queue.front();
        }
		void add_core_job_q(int job)
        {
            core_job_queue.push(job);
        }
		void pop_core_job_q()
        {
            core_job_queue.pop();
        }

		//getter/setter to check if it is registered to any of the dispatchers' queue
		bool is_inside_disp()
        {
            return inside_disp;
        }
		void it_is_now()
        {
            inside_disp = true;
        }
		void now_its_not()
        {
            inside_disp = false;
        }

	private:
		std::queue<int> core_job_queue;
		bool inside_disp = false;
		bool green_node ;//future use

		friend class Core_topology;
		friend class Core_idle;
		friend class Core_serve;

		Core_topology core_state_topology;
		Core_idle core_state_idle;
		Core_serve core_state_serve;

		State_manager<Core>* core_curr_state;
		States core_prev_state;

		Events core_curr_event;

		void change_state(States);
		void set_event(Events);
};

#endif
