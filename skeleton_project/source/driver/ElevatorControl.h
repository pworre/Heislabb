#pragma once

#include "elevatorStateMachine.h"

struct Elevator {
    ElevatorState state = MOVING_DOWN;
};

ElevatorState ctrl_getElevatorState();
