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

void Hardware::OpenDoors() {
    // opens the elevator's doors.
}

int Hardware::GoToFloor(int floor_numbers) {
    /*
     * sends the elevator to floor "floor_number" and opens the doors, it receives values from a sensor
     * on the door that checks if there is someone at the door and keeps the doors open until
     * this person goes.
     * it returns a value that represents:
     * (number of people untried to the elevator) - (number of people left the elevator).
     */

    return 0;

}

Button Hardware::WaitForButtonPress(int floor_number) {
    /*
     * blocks the calling thread until either UP or DOWN is pressed,
     * then returns which button was pressed.
     */

    return DOWN;
}
