#include "queModule.h"
#include "stdlib.h"

void que_addOrder(struct Orders **hode, int orderToAdd) {
    struct Orders *head = NULL;
    // Saves the adress for Order-type in head and allocate memory
    head = (struct Orders *)malloc(sizeof(struct Orders));
    head->order_floor = orderToAdd;


void que_checkQue(struct Elevator* anElevator, struct Orders* que) {
    if ((que->order < anElevator->lastFloor) && (anElevator->state != MOVING_UP)) {
        elevio_motorDirection(DIRN_DOWN);
        ctrl_updateElevatorState(anElevator, MOVING_DOWN);
    } else if ((que->order > anElevator->lastFloor) && (anElevator->state != MOVING_DOWN)) {
        elevio_motorDirection(DIRN_UP);
        ctrl_updateElevatorState(anElevator, MOVING_DOWN);
    }
}

void que_addOrder(struct Orders **hode, int order) {
>>>>>>> 10809fa6732b46b8fc74a6b08cc1c455a74d2afa
    struct Orders* new_Order = ()
};

void que_removeCompletedOrder(struct Orders);
void que_clearOrders(struct Orders);

