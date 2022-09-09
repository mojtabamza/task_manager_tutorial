
#pragma once
#include "inc.hpp"

/*struct task_t {
    int interval;
    void(*task)(void);
    int task_exe_time;
};*/

class Systick_t {
public:
    static Systick_t* get_instance(void);
    void add_task(void(*task)(void), int interval);
    int get_tick(void);
    void tick();
    void systick_isr(void);
    void systick_handler(void);
    vector<bool> flags;
private:
    struct task_t {
        int interval;
        void(*task)(void);
        int task_exe_time;
    };
    Systick_t();
    int tick_counter;
    vector<task_t*> task;

};

