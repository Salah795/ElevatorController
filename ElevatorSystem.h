//
// Created by Salah Taher on 10/3/2026.
//

#ifndef ELEVATORCONTROLLER_ELEVATORSYSTEM_H
#define ELEVATORCONTROLLER_ELEVATORSYSTEM_H
#include "Elevator.h"
#include "Floor.h"

// TODO SHOULD RECHECK THIS CLASS AND EVERYTHING RELATED TO IT.
class ElevatorSystem {
    Elevator elevator;
    std::vector<std::unique_ptr<Floor>> floors;
    explicit ElevatorSystem(int floors_number);

public:
    ElevatorSystem(const ElevatorSystem&) = delete;
    ElevatorSystem& operator=(const ElevatorSystem&) = delete;
    ElevatorSystem(ElevatorSystem&&) = delete;
    ElevatorSystem& operator=(ElevatorSystem&&) = delete;
    static ElevatorSystem& getInstance(int floors_number);
    void start();
};


#endif //ELEVATORCONTROLLER_ELEVATORSYSTEM_H
