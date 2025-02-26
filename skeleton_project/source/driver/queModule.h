#pragma once
#include "elevatorControl.h"

struct Orders {
    int order;
    struct Orders *next;
};

void que_checkQue(struct Elevator* anElevator, struct Orders* que);
void que_addOrder(struct Orders **hode, int order);
void que_removeCompletedOrder(struct Orders);
void que_clearOrders(struct Orders);

