//
// Created by Salah Taher on 10/2/2026.
//

#ifndef ELEVATORCONTROLLER_HARDWARE_H
#define ELEVATORCONTROLLER_HARDWARE_H


enum Button {
    UP, DOWN
};

namespace  Hardware
{
    int GetCurrentElevatorFloor();
    int GetCurrentElevatorVelocity();
    void StopElevator();
    void GoToFloor(int floor_numbers);
    Button WaitForButtonPress(int floor_number);


};


#endif //ELEVATORCONTROLLER_HARDWARE_H
