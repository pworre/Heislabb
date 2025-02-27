#pragma once

#include "elevatorStateMachine.h"
#include "elevio.h"
#include "queModule.h"
#include "stdlib.h"

struct Elevator {
    ElevatorState state;
    int lastFloor;
    int run;
    int viabas;             // variable which is 1 if the elevator will stop on either way for bringing more PAX
};

ElevatorState ctrl_getElevatorState(struct Elevator* anElevator);
void ctrl_updateElevatorState(struct Elevator* anElevator, ElevatorState aState);
void ctrl_setFloor(struct Elevator* anElevator, int floor);

void ctrl_startup(struct Elevator* anElevator);
void ctrl_run(struct Elevator* anElevator, struct Orders* order);