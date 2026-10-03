//
// Created by Salah Taher on 10/2/2026.
//

#include "Elevator.h"

void Elevator::add_destination(const int floor_number, const bool inside, const Direction direction) {
    /*
     * Adds a new destination request to the elevator.
     * A request is ignored if the same floor already has a pending request.
     * If the elevator is already at the requested floor, the elevator is
     * stopped immediately instead of adding a new request.
     *
     * Requests made from inside the elevator are assigned a negative timestamp,
     * while requests made from outside are assigned a positive timestamp.
     * The timestamp is used by ComparePriority to determine the order in which
     * pending requests are processed.
     */

    this->data_mutex.lock();

    if (this->floors_map.find(floor_number) != this->floors_map.end()) {
        this->data_mutex.unlock();
        return;

    }
    const int current_floor = Hardware::GetCurrentElevatorFloor();
    if (current_floor == floor_number) {
        this->data_mutex.unlock();
        Hardware::StopElevator();
        return;
    }

    if (inside) {
        this->floors_priority.push({floor_number, direction, -(++this->timer)});
    }
    else {
        this->floors_priority.push({floor_number, direction, ++this->timer});
    }
    this->floors_map[floor_number] = {floor_number, direction, this->timer};
    this->data_mutex.unlock();
    this->request_available.notify_one();
}

void Elevator::run() {
    /*
     * Runs the elevator worker thread and processes pending destination requests.
     * While moving toward the requested destination, the elevator checks
     * every floor for pending requests made in the same direction. Such
     * requests are served along the way, preventing the elevator from
     * unnecessarily passing passengers who are waiting in its current
     * direction.
     */

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

            for (int floor = current_floor; floor != next_floor;
                floor += static_cast<int>(this->current_direction)) {
                if ((this->floors_map.find(floor) != this->floors_map.end()) &&
                    (this->floors_map[floor].direction == this->current_direction)) {
                    this->floors_map.erase(floor);
                    lock.unlock();
                    Hardware::GoToFloor(floor);
                    lock.lock();
                }
            }

            this->floors_map.erase(next_floor);
            lock.unlock();
            Hardware::GoToFloor(next_floor);
        }
    }
}
