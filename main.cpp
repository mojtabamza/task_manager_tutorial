
#include "inc.hpp"
#include "systick.hpp"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


void task_A(void) {
    cout << "TASK A!" << endl;
}

void task_B(void) {
    cout << "TASK B!" << endl;
}


int main(void) {

    Systick_t::get_instance()->add_task(task_A, 10);
    Systick_t::get_instance()->add_task(task_B, 14);

    while(1) {
        Systick_t::get_instance()->systick_handler();

        if(Systick_t::get_instance()->flags[0]) {
            task_A();
            Systick_t::get_instance()->flags[0] = false;
        }
        if(Systick_t::get_instance()->flags[1]) {
            task_B();
            Systick_t::get_instance()->flags[1] = false;
        }
    }

    return 0;
}

