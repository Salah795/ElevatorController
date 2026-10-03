# ElevatorController

System Architecture

The solution is divided into three main classes: ElevatorSystem, Elevator, and Floor.

1. ElevatorSystem

ElevatorSystem is the main controller of the system and is responsible for creating and starting all system components.

Contains one Elevator object.
Contains a collection of Floor objects.
Each Floor receives a reference to the same Elevator.
Creates one Floor for each floor in the building.
Starts the elevator thread and then starts the worker thread of every floor.