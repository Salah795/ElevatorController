//
// Created by Salah Taher on 10/2/2026.
//

#ifndef ELEVATORCONTROLLER_ELEVATOR_H
#define ELEVATORCONTROLLER_ELEVATOR_H

#include <cmath>
#include <queue>
#include <vector>
#include <unordered_map>
#include <condition_variable>
#include <thread>

#include "Hardware.h"

// TODO need to deal with the direction synchronization issue.
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
    /*
     * Defines the priority order of elevator requests.
     * Requests made from inside the elevator have negative timestamps,
     * while requests made from outside have positive timestamps.
     * The priority queue therefore processes:
     *    1. Inside requests before outside requests.
     *    2. Among requests of the same type, the oldest request first,
     *       determined by the absolute value of the timestamp.
     *
     * This allows requests from passengers already inside the elevator
     * to take priority over new external requests.
     */

    bool operator() (const Request& first_request, const Request& second_request) const {
        if (first_request.time > 0 && second_request.time < 0) {
            return true;
        }

        if ((first_request.time < 0 && second_request.time < 0) ||
            (first_request.time > 0 && second_request.time > 0)) {
            return abs(first_request.time) > abs(second_request.time);
        }

        return false;
    }
};

class Elevator
{
    int timer;
    std::thread worker;
    std::mutex data_mutex;
    Direction current_direction;
    std::condition_variable request_available;
    std::unordered_map<int, Request> floors_map;
    std::priority_queue<Request, std::vector<Request>, ComparePriority> floors_priority;

public:
    Elevator(): timer(0), current_direction(Direction::NON) {}
    void add_destination(int floor_number, bool inside, Direction direction);
    Direction get_direction() const {return this->current_direction;}
    void start();
    int get_floor() {return Hardware::GetCurrentElevatorFloor();}
    void run();
};


#endif //ELEVATORCONTROLLER_ELEVATOR_H
