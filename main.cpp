
#include "inc.hpp"
#include "systick.hpp"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

bool flag_a = false;
bool flag_b = false;
void task_a(void) {
    flag_a = true;
}
void task_b(void) {
    flag_b = true;
}

void task_A(void) {
    flag_a = false;
    cout << "TASK A!" << endl;
}

void task_B(void) {
    flag_b = false;
    cout << "TASK B!" << endl;
}


int main(void) {

    Systick_t::get_instance()->add_task(task_a, 10);
    Systick_t::get_instance()->add_task(task_b, 14);

    while(1) {
        Systick_t::get_instance()->systick_handler();
        if(flag_a){
            task_A();
        }
        if(flag_b){
            task_B();
        }
        /*if(Systick_t::get_instance()->flags[0]) {
            task_A();
            Systick_t::get_instance()->flags[0] = false;
        }
        if(Systick_t::get_instance()->flags[1]) {
            task_B();
            Systick_t::get_instance()->flags[1] = false;
        }*/
    }

    return 0;
}

