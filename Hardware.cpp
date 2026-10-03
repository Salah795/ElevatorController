//
// Created by Salah Taher on 10/2/2026.
//

#include "Hardware.h"


int Hardware::GetCurrentElevatorFloor() {
    // returns the current floor of the elevator.
    return 0;
}

int Hardware::GetCurrentElevatorVelocity() {
    // returns the current velocity of the elevator.
    return 0;
}

void Hardware::StopElevator() {
    // stop the elevator at the current floor (first checks if it's possible) and opens the doors for a while.
}

void Hardware::GoToFloor(int floor_numbers) {
    /*
     * sends the elevator to floor "floor_number" and opens the doors, it receives values from a sensor
     * on the door that checks if there is someone at the door and keeps the doors open until
     * this person goes.
     */
}

Button Hardware::WaitForButtonPress(int floor_number) {
    /*
     * blocks the calling thread until either UP or DOWN is pressed,
     * then returns which button was pressed.
     */

    return DOWN;
}
