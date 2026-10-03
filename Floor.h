//
// Created by Salah Taher on 10/3/2026.
//

#ifndef ELEVATORCONTROLLER_FLOOR_H
#define ELEVATORCONTROLLER_FLOOR_H
#include "Elevator.h"


class Floor {
    const int number;
    std::thread worker;
    Elevator& elevator;

public:
    Floor(const int floor_number, Elevator& elevator): number(floor_number), elevator(elevator) {}
    void start();
    void run() const;
};


#endif //ELEVATORCONTROLLER_FLOOR_H
