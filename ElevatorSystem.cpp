//
// Created by Salah Taher on 10/3/2026.
//

#include "ElevatorSystem.h"


ElevatorSystem::ElevatorSystem(int floors_number) {
    this->elevator = new Elevator();
    for (int index = 0; index < floors_number; index++) {
        this->floors.push_back(new Floor(index, *this->elevator));
    }
}

void ElevatorSystem::start() const {
    this->elevator->start();
    for (const auto & floor : this->floors) {
        floor->start();
    }
}
