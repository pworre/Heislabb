#pragma once
#include "elevatorControl.h"


// Linked list for que-system
struct Orders {
    int orderFloor;

    // Self-referential structure pointing to next the order and info about the next order
    struct Orders *next;
};

void que_addOrder(struct Orders **hode, int order_floor);
void que_checkQue(struct Elevator* anElevator, struct Orders* que);
void que_addOrder(struct Orders **hode, int order);
void que_removeCompletedOrder(struct Orders);
void que_clearOrders(struct Orders);

