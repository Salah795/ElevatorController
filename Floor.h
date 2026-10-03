//
// Created by Salah Taher on 10/3/2026.
//

#ifndef ELEVATORCONTROLLER_FLOOR_H
#define ELEVATORCONTROLLER_FLOOR_H
#include "Elevator.h"


class Floor {
    bool up_flag;
    bool down_flag;
    const int number;
    std::thread worker;
    Elevator& elevator;

public:
    Floor(const int floor_number, Elevator& elevator):
    up_flag(false), down_flag(false), number(floor_number), elevator(elevator) {}
    void start() {this->worker = std::thread(&Floor::run, this);}
    void run() const;
};


#endif //ELEVATORCONTROLLER_FLOOR_H
