//
// Created by Salah Taher on 10/2/2026.
//

#include "Elevator.h"

void Elevator::add_destination(int floor_number, bool inside, Direction direction) {
    this->data_mutex.lock();

    if (this->floors_map.find(floor_number) != this->floors_map.end()) {
        this->floors_map.erase(floor_number);
    }
    else {
        const int current_floor = Hardware::GetCurrentElevatorFloor();
        const int current_velocity = Hardware::GetCurrentElevatorVelocity();
        if ((current_floor == floor_number) && (current_velocity == 0)) {
            Hardware::OpenDoors();
            this->data_mutex.unlock();
            return;
        }

        if (inside) {
            this->floors_priority.push({floor_number, direction, -(++this->timer)});
        }
        else {
            this->floors_priority.push({floor_number, direction, ++this->timer});
        }
        this->floors_map[floor_number] = {floor_number, direction, this->timer};
    }
    this->request_available.notify_one();
    this->data_mutex.unlock();
}

void Elevator::run() {
    
}
