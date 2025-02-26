#pragma once
#include "elevatorControl.h"

struct Orders {
    int order;
    struct Orders *next;
};

void que_checkQue(struct Elevator* anElevator, struct Orders* que);
