#pragma once

#include "elevatorStateMachine.h"
#include "elevio.h"

struct Elevator {
    ElevatorState state;
};

ElevatorState ctrl_getElevatorState(Elevator* anElevator);
void ctrl_updateElevatorState(Elevator* anElevator, ElevatorState aState);

void ctrl_startup(Elevator* anElevator);