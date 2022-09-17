
#include "systick.hpp"



Systick_t* Systick_t::get_instance(void) {
	static Systick_t* instance = NULL;
	if(instance == NULL) {
		instance = new Systick_t();
	}
	return instance;
}

void Systick_t::add_task(void(*task)(void), int interval) {
    cout << "hello systick" << endl;
    task_t *new_task = new task_t();
    new_task->interval = interval;
    new_task->task = task;
    new_task->task_exe_time = this->tick_counter + new_task->interval;
    this->task.push_back(new_task);
    this->flags.push_back(false);
}

void Systick_t::systick_isr(void) {
    this->tick();
    for(auto i = 0; i < this->task.size(); i++) {
        if(task[i]->task_exe_time == tick_counter) {
            //task[i]->task();
            task[i]->task_exe_time = tick_counter + task[i]->interval;
            flags[i] = true;
        }
    }

}
void Systick_t::systick_handler(void) {
    static int timer = 0;
    if(++timer >= 100000) {
        this->systick_isr();
        timer = 0;
    }
}

Systick_t::Systick_t() {
    this->tick_counter = 0;
}

int Systick_t::get_tick() {
    return tick_counter;
}
void Systick_t::tick() {
    tick_counter++;
    cout << "tick_counter = " << tick_counter << endl;
}
