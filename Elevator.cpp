//
// Created by Salah Taher on 10/2/2026.
//

#include "Elevator.h"

void Elevator::add_destination(const int floor_number, const bool inside, const Direction direction) {
    this->data_mutex.lock();

    if (this->floors_map.find(floor_number) != this->floors_map.end()) {
        this->floors_map.erase(floor_number);
    }
    else {
        const int current_floor = Hardware::GetCurrentElevatorFloor();
        const int current_velocity = Hardware::GetCurrentElevatorVelocity();
        if (current_floor == floor_number && current_velocity == 0) {
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
    while (true) {
        std::unique_lock<std::mutex> lock(this->data_mutex);
        this->request_available.wait(lock, [&]{return !this->floors_map.empty();});
        int next_floor = this->floors_priority.top().floor;
        this->floors_priority.pop();
        if (this->floors_map.find(next_floor) != this->floors_map.end()) {
            const int current_floor = Hardware::GetCurrentElevatorFloor();
            if (next_floor - current_floor > 0) {
                this->current_direction = Direction::UP;
            }
            else {
                this->current_direction = Direction::DOWN;
            }

            for (int floor = current_floor; floor != next_floor; floor += static_cast<int>(this->current_direction)) {
                if ((this->floors_map.find(floor) != this->floors_map.end()) &&
                    (this->floors_map[floor].direction == this->current_direction)) {
                    this->floors_map.erase(floor);
                    this->people_number += Hardware::GoToFloor(floor);
                }
            }

            this->floors_map.erase(next_floor);
            this->people_number += Hardware::GoToFloor(next_floor);
            lock.unlock();
        }
    }
}
