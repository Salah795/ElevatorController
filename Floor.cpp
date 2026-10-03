//
// Created by Salah Taher on 10/3/2026.
//

#include "Floor.h"


void Floor::start() {
    if (!this->worker.joinable()) {
        this->worker = std::thread(&Floor::run, this);
    }
}

void Floor::run() const {
    /*
     * Continuously monitors the floor's elevator buttons and forwards
     * button-press events to the associated elevator.
     * UP and DOWN are handled independently because both buttons may be
     * pressed and generate separate elevator requests.
     */

    while (true) {
        const Button pressed_button = Hardware::WaitForButtonPress(this->number);
        if (pressed_button == UP) {
            this->elevator.add_destination(this->number, false, Direction::UP);
        }
        if (pressed_button == DOWN) {
            this->elevator.add_destination(this->number, false, Direction::DOWN);
        }
    }
}
