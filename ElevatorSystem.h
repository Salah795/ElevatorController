//
// Created by Salah Taher on 10/3/2026.
//

#ifndef ELEVATORCONTROLLER_ELEVATORSYSTEM_H
#define ELEVATORCONTROLLER_ELEVATORSYSTEM_H
#include "Elevator.h"
#include "Floor.h"


class ElevatorSystem {
    /**
 * ElevatorSystem is responsible for managing the elevator and all floors
 * in the building. It creates the required components, connects each
 * floor to the elevator, and starts their worker threads.
 *
 * The class is implemented as a Singleton to ensure that only one
 * ElevatorSystem instance exists and serves as the central controller
 * of the entire system.
 */

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
