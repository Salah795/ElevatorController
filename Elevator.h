//
// Created by Salah Taher on 10/2/2026.
//

#ifndef ELEVATORCONTROLLER_ELEVATOR_H
#define ELEVATORCONTROLLER_ELEVATOR_H

#include <queue>
#include <vector>
#include <functional>
#include <unordered_map>
#include <condition_variable>


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
    bool operator() (const Request& first_request, const Request& second_request) {
        return (first_request.time < second_request.time) && !(first_request.time >= 0 && second_request.time < 0);
    }
};

class Elevator
{
private:
    int timer;
    int people_number;
    std::mutex data_mutex;
    Direction current_direction;
    std::condition_variable request_available;
    std::unordered_map<int, Request> floors_map;
    std::priority_queue<Request, std::vector<Request>, ComparePriority> floors_priority;

public:
    
};


#endif //ELEVATORCONTROLLER_ELEVATOR_H
