# ElevatorController

## System Architecture

The solution is divided into three main classes: `ElevatorSystem`, `Elevator`, and `Floor`.

### 1. ElevatorSystem

ElevatorSystem is the main controller of the system and is responsible for creating and starting all system components.

* Contains one Elevator object.
* Contains a collection of Floor objects.
* Each Floor receives a reference to the same Elevator.
* Creates one Floor for each floor in the building.
* Starts the elevator thread and then starts the worker thread of every floor.

### 2. Elevator

Elevator is responsible for managing and executing elevator requests.

It contains:

* A worker thread responsible for processing requests.
* A `std::mutex` protecting shared request data.
* A `std::condition_variable` used to put the elevator thread to sleep when there are no pending requests.
* A `std::priority_queue` containing pending requests ordered according to their priority.
* An `unordered_map` containing currently active requests.
* The current elevator direction.
* A timer used to determine request ordering.

The elevator worker thread continuously:

1. Waits for a request using the condition variable.
2. Selects the highest-priority request.
3. Determines the direction toward the requested floor.
4. Moves toward the destination one floor at a time.
5. While moving, checks for additional requests on the way in the same direction and serves them.
6. Reaches the original destination.
7. Returns to waiting for the next request.

The mutex protects the shared request structures, while it is released during physical elevator movement so that 
floor threads can add new requests concurrently.

### 3. Floor

Each Floor represents one floor of the building.

Every Floor contains:

* Its floor number.
* A reference to the central Elevator.
* Its own worker thread.

The floor thread continuously waits for a button press using:

```cpp
Hardware::WaitForButtonPress(number);
```

When a button is pressed, the floor sends the corresponding request to the elevator:

```text
UP button   ──► Elevator::add_destination(floor, false, UP)
DOWN button ──► Elevator::add_destination(floor, false, DOWN)
```

The UP and DOWN requests are handled independently, allowing both buttons to generate requests.

---

## Threads

The system uses multiple threads:

There is:

* 1 worker thread for the Elevator
* 1 worker thread for every Floor

Therefore, for a building with N floors, the system uses:

```text
N + 1 worker threads
```

The Floor threads act as producers of elevator requests, while the Elevator thread acts as the consumer and scheduler 
of those requests.

---

## Synchronization

Synchronization between the floor threads and the elevator thread is implemented using:

* `std::mutex` — protects shared elevator request data.
* `std::condition_variable` — allows the elevator thread to sleep while there are no requests and wake up when a floor 
* adds a new request.
* `std::priority_queue` — determines which pending request should be processed next.
* `std::unordered_map` — keeps track of currently active requests and allows the elevator to detect requests 
* encountered while traveling.

Overall, the architecture separates input handling (Floor), request scheduling and movement (Elevator), and system 
initialization and ownership (ElevatorSystem).

---

# Elevator System Algorithm

## 1. System Initialization

* Create one Elevator object.
* Create a Floor object for each floor in the building.
* Each Floor receives a reference to the same Elevator.
* Start one worker thread for the Elevator.
* Start one worker thread for every Floor.

## 2. Floor Request Handling

Each floor runs continuously in its own thread:

1. Wait for a button press using `Hardware::WaitForButtonPress()`.
2. If the UP button is pressed:

    * Create an external request for the current floor with direction UP.
    * Send the request to the elevator.
3. If the DOWN button is pressed:

    * Create an external request for the current floor with direction DOWN.
    * Send the request to the elevator.
4. Continue waiting for the next button press.

## 3. Adding an Elevator Request

When a request is received by the elevator:

1. Lock the shared request data using `data_mutex`.
2. Check whether the floor already has a pending request.
3. If it does, ignore the new request.
4. Check whether the elevator is already at the requested floor.
5. If it is, stop the elevator and do not add a new destination.
6. Assign a timestamp to the request:

    * Inside request: negative timestamp.
    * Outside request: positive timestamp.
7. Insert the request into the priority queue.
8. Store the request in `floors_map`.
9. Unlock the mutex.
10. Notify the elevator worker thread that a new request is available.

## 4. Selecting the Next Destination

The elevator worker thread continuously executes:

1. Wait on the condition variable until there is at least one pending request.
2. Lock the request data.
3. Take the highest-priority request from the priority queue.
4. Remove the request from the priority queue.
5. Verify that the request still exists in `floors_map`.
6. If it does not exist, ignore it and continue.
7. Read the current elevator floor.
8. Determine the elevator's direction:

    * If destination > current floor → UP.
    * Otherwise → DOWN.

## 5. Moving Toward the Destination

While the elevator is moving toward the selected destination:

1. Examine each floor between the current floor and the destination.
2. Check whether there is a pending request on that floor.
3. If a request exists and its direction matches the current elevator direction:

    * Remove the request from `floors_map`.
    * Temporarily release the mutex.
    * Move the elevator to that floor.
    * Reacquire the mutex.
4. If there is no matching request, continue toward the destination.

## 6. Reaching the Main Destination

When the elevator reaches the selected destination:

1. Remove the destination from `floors_map`.
2. Release the mutex.
3. Move the elevator to the destination using `Hardware::GoToFloor()`.
4. Return to the waiting state.

## 7. Continuous Operation

The elevator thread and all floor threads run continuously.

---

# Priority Algorithm

Requests are prioritized according to their timestamp:

* Inside-elevator requests have higher priority than outside requests.
* Among requests of the same type, the older request has higher priority.

---

# Is there some problem with the presented logic? Do you have any suggestion how to improve it?

I think there is a problem with handling floor requests when the elevator is not free.
I think that in all cases, we should process the requests. However, when there is a request from inside the elevator, 
it should always have higher priority than an outside request, even if the outside request was made earlier.
In this case, the elevator will go to the floor requested from outside only after all the internal requests have 
been completed, unless the outside request is on the way and in the same direction as the elevator.

---

# What threads do you need? 

The system requires one worker thread for the elevator and one worker thread for each floor.

---

# What Can Run in Parallel?

The following operations can run in parallel:

All floor threads can wait for button presses simultaneously.
A floor can submit a new request while the elevator is physically moving.
Multiple floors can generate requests concurrently.
The elevator can continue its movement while floor threads are waiting for or generating new requests.

The shared request data is protected by std::mutex to prevent concurrent access from causing inconsistencies.

---

# What Must Be Asynchronous?

Handling button presses must be asynchronous because the system cannot know when a passenger will press a button. 
Each floor therefore waits for its own button events independently.
The elevator also uses a std::condition_variable so that its worker thread sleeps when there are no pending 
requests and is asynchronously notified when a new request is added.

---

# How would change your solution if there are two elevators in the building?

I would change the ElevatorSystem class to manage multiple elevators instead of a single elevator. 
The ElevatorSystem would be implemented as a Singleton so that there is only one central controller 
responsible for all elevators and floors.
The system would contain two Elevator objects, each with its own worker thread and request queue. 
The Floor objects would send their requests to the ElevatorSystem instead of directly to a specific elevator.

When an external request is received, the ElevatorSystem would select the most suitable elevator based on factors 
such as whether the elevator is free, its current floor, and its current direction. In particular, 
a free elevator that is closest to the requested floor would normally be selected.
After selecting an elevator, the request would be assigned to that elevator, which would then process it using the same
request-priority and movement logic as in the single-elevator solution.

The Hardware interface would also be modified to support multiple elevators. Hardware functions would receive the 
elevator ID so that the system can control the correct elevator.