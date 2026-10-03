//
// Created by Salah Taher on 10/3/2026.
//

#include "ElevatorSystem.h"


ElevatorSystem::ElevatorSystem(const int floors_number) {
    for (int index = 0; index < floors_number; index++) {
        this->floors.push_back(std::make_unique<Floor>(index, this->elevator));
    }
}

void ElevatorSystem::start() {
    this->elevator.start();
    for (const auto & floor : this->floors) {
        floor->start();
    }
}
