//
// Created by Salah Taher on 10/3/2026.
//

#include "Floor.h"


void Floor::run() const {
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
