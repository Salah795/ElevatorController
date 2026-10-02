//
// Created by Salah Taher on 10/2/2026.
//

#ifndef ELEVATORCONTROLLER_HARDWARE_H
#define ELEVATORCONTROLLER_HARDWARE_H
#include "Elevator.h"


namespace  Hardware
{
    int GetCurrentElevatorFloor();
    int GetCurrentElevatorVelocity();
    void OpenDoors();
    int GoToFloor(int floor_numbers);

};


#endif //ELEVATORCONTROLLER_HARDWARE_H
