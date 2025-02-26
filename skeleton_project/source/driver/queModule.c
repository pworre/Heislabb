#include "queModule.h"
#include "stdlib.h"

void que_addOrder(struct Orders **hode, int requestedFloor) {
    struct Orders *head = NULL;
    // Saves the adress for Order-type in head and allocate memory
    head = (struct Orders *)malloc(sizeof(struct Orders));
    head->orderFloor = requestedFloor;
}

void que_checkQue(struct Elevator* anElevator, struct Orders* que) {
    if ((que->orderFloor < anElevator->lastFloor) && (anElevator->state != MOVING_UP)) {
        elevio_motorDirection(DIRN_DOWN);
        ctrl_updateElevatorState(anElevator, MOVING_DOWN);
    } else if ((que->orderFloor > anElevator->lastFloor) && (anElevator->state != MOVING_DOWN)) {
        elevio_motorDirection(DIRN_UP);
        ctrl_updateElevatorState(anElevator, MOVING_DOWN);
    }
}

//void que_addOrder(struct Orders **hode, int order) {
//    struct Orders* new_Order = ();
//};

void que_removeCompletedOrder(struct Orders);
void que_clearOrders(struct Orders);

