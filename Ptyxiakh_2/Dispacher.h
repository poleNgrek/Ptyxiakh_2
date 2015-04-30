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
	d)functions that extend dispacher's functionality such as
		1)schedule_event
		2)assign_job (to a core)
		3)fill_core_queue

**/

#ifndef DISPACHER_H_
#define DISPACHER_H_

#include "State_manager.h"
#include <queue>
#include "Core.h"

using namespace std;

enum class States;
enum class Events;

class Dispacher;
//class Core; // so we can use Core class inside Dispacher functions

class Dispacher_serve : public State_manager<Dispacher>
{
	public:
		Dispacher_serve(Dispacher&);

		void on_entry();
		void on_exit();
		void handle_event(Events);

};

class Dispacher_idle : public State_manager<Dispacher>
{
	public:
		Dispacher_idle(Dispacher&);

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

class Dispacher
{
	public:
		Dispacher();
		~Dispacher();

		void schedule_event(Events);
		void assign_job(int job);
		void fill_core_queue();

		/* Getters for dispacher queues */

		int get_job_q() {return disp_job_queue.front();}

		Core& get_core_q() {return disp_core_queue.front();}

		/*Adders-Setters for dispacher queues */

		void add_job_q(int job) {disp_job_queue.push(job);}

		void add_core_q(Core core) {disp_core_queue.push(core);}

		/*pop functions*/

		void pop_job_q() {disp_job_queue.pop();}

		void pop_core_q() {	disp_core_queue.pop();}

	private:
		queue<int> disp_job_queue;//queue for incoming random numbers
		queue<Core> disp_core_queue; // somehow it should include core handlers

		friend class Dispacher_serve;
		friend class Dispacher_idle;
		//friend class Dispacher_exit;

		Dispacher_serve disp_state_serve;
		Dispacher_idle disp_state_idle;
		//Dispacher_exit disp_state_exit;

		State_manager<Dispacher>* disp_curr_state;
		States disp_prev_state;

		void change_state(States);
};

#endif
