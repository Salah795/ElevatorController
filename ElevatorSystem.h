//
// Created by Salah Taher on 10/3/2026.
//

#ifndef ELEVATORCONTROLLER_ELEVATORSYSTEM_H
#define ELEVATORCONTROLLER_ELEVATORSYSTEM_H
#include "Elevator.h"
#include "Floor.h"


class ElevatorSystem {
    Elevator elevator;
    std::vector<std::unique_ptr<Floor>> floors;

public:
    explicit ElevatorSystem(int floors_number);
    void start();
};


#endif //ELEVATORCONTROLLER_ELEVATORSYSTEM_H
