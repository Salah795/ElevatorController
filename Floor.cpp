//
// Created by Salah Taher on 10/3/2026.
//

#include "Floor.h"

// STILL THERE IS A REAL ISSUE WITH THIS METHOD!!!!!!!!!!
void Floor::run() {
    while (true) {
        std::unique_lock<std::mutex> lock(this->buttons_mutex);

        this->elevator_required.wait(lock, [&]{return (this->up_flag || this->down_flag);});

        if (this->up_flag) {
            this->elevator.add_destination(this->number, false, Direction::UP);
        }
        if (this->down_flag) {
            this->elevator.add_destination(this->number, false, Direction::DOWN);
        }
    }
}
