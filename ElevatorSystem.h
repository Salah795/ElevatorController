//
// Created by Salah Taher on 10/3/2026.
//

#ifndef ELEVATORCONTROLLER_ELEVATORSYSTEM_H
#define ELEVATORCONTROLLER_ELEVATORSYSTEM_H
#include "Elevator.h"
#include "Floor.h"

// TODO SHOULD DO A RECHECK ON THIS CLASS AND IT'S METHODS IMPLEMENTATION.
class ElevatorSystem {
private:
    Elevator *elevator;
    std::vector<Floor*> floors;

public:
    explicit ElevatorSystem(int floors_number);
    void start() const;
};


#endif //ELEVATORCONTROLLER_ELEVATORSYSTEM_H
