#ifndef CORE_H_
#define CORE_H_

#include "State_manager.h"
#include <queue>

using namespace std;

enum class States;
enum class Events;

class Core;
class Dispacher;

class Core_topology : public State_manager<Core>
{
	public:
		Core_topology(Core&);
		
		void on_entry();
		void on_exit();
		void handle_event(Events);
};

class Core_idle : public State_manager<Core>
{
	public:
		Core_idle(Core&);
		
		void on_entry();
		void on_exit();
		void handle_event(Events);
};

class Core_serve : public State_manager<Core>
{
	public:
		Core_serve(Core&);
		
		void on_entry();
		void on_exit();
		void handle_event(Events);
};

class Core
{
	public:
		Core();
		~Core();
		
		void schedule_event(Events);
		Events get_event();
	
		int get_core_job_q() {return core_job_queue.front();}
		void add_core_job_q(int job) {core_job_queue.push(job);}
		void pop_core_job_q() {core_job_queue.pop();}
		
	private:
		queue<int> core_job_queue;
		
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