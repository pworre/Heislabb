#pragma once
#include "elevatorControl.h"

typedef enum { 
    MOVING_DOWN   = 0,
    STATIONARY   = 1,
    MOVING_UP     = 2
} ElevatorState;

void SM_updateElevatorState();
