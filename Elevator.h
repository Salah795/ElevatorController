//
// Created by Salah Taher on 10/2/2026.
//

#ifndef ELEVATORCONTROLLER_ELEVATOR_H
#define ELEVATORCONTROLLER_ELEVATOR_H

#include <queue>
#include <vector>
#include <unordered_map>
#include <condition_variable>
#include <thread>

#include "Hardware.h"


enum class Direction {
    DOWN = -1,
    NON = 0,
    UP = 1
};

struct Request {
    int floor;
    Direction direction;
    int time;
};

struct ComparePriority {
    bool operator() (const Request& first_request, const Request& second_request) const {
        return (first_request.time < second_request.time) && !(first_request.time >= 0 && second_request.time < 0);
    }
};

class Elevator
{
    int timer;
    int people_number;
    std::thread worker;
    std::mutex data_mutex;
    Direction current_direction;
    std::condition_variable request_available;
    std::unordered_map<int, Request> floors_map;
    std::priority_queue<Request, std::vector<Request>, ComparePriority> floors_priority;

public:
    Elevator(): timer(0), people_number(0), current_direction(Direction::NON) {}
    void add_destination(int floor_number, bool inside, Direction direction);
    Direction get_direction() const {return this->current_direction;}
    void start() {this->worker = std::thread(&Elevator::run, this);}
    int get_floor() {return Hardware::GetCurrentElevatorFloor();}
    bool is_free() const {return this->people_number == 0;}
    void run();
};


#endif //ELEVATORCONTROLLER_ELEVATOR_H
