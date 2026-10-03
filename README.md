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

2. Elevator

Elevator is responsible for managing and executing elevator requests.

It contains:

A worker thread responsible for processing requests.
A std::mutex protecting shared request data.
A std::condition_variable used to put the elevator thread to sleep when there are no pending requests.
A std::priority_queue containing pending requests ordered according to their priority.
An unordered_map containing currently active requests.
The current elevator direction.
A timer used to determine request ordering.

The elevator worker thread continuously:

Waits for a request using the condition variable.
Selects the highest-priority request.
Determines the direction toward the requested floor.
Moves toward the destination one floor at a time.
While moving, checks for additional requests on the way in the same direction and serves them.
Reaches the original destination.
Returns to waiting for the next request.

The mutex protects the shared request structures, while it is released during physical elevator movement so that floor threads can add new requests concurrently.

3. Floor

Each Floor represents one floor of the building.

Every Floor contains:

Its floor number.
A reference to the central Elevator.
Its own worker thread.

The floor thread continuously waits for a button press using:

Hardware::WaitForButtonPress(number);

When a button is pressed, the floor sends the corresponding request to the elevator:

UP button   ──► Elevator::add_destination(floor, false, UP)
DOWN button ──► Elevator::add_destination(floor, false, DOWN)

The UP and DOWN requests are handled independently, allowing both buttons to generate requests.

Threads

The system uses multiple threads:

There is:

1 worker thread for the Elevator
1 worker thread for every Floor

Therefore, for a building with N floors, the system uses:

N + 1 worker threads

The Floor threads act as producers of elevator requests, while the Elevator thread acts as the consumer and 
scheduler of those requests.

Synchronization

Synchronization between the floor threads and the elevator thread is implemented using:

std::mutex — protects shared elevator request data.
std::condition_variable — allows the elevator thread to sleep while there are no requests and wake up when a floor 
adds a new request.
std::priority_queue — determines which pending request should be processed next.
std::unordered_map — keeps track of currently active requests and allows the elevator to detect requests 
encountered while traveling.

Overall, the architecture separates input handling (Floor), request scheduling and movement (Elevator), 
and system initialization and ownership (ElevatorSystem).