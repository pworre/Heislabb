#include "queModule.h"
#include "stdlib.h"


void que_addOrder(struct Orders **head, int requestedFloor) {
    struct Orders *newOrder = NULL;
    // Saves the adress for Order-type in head and allocate memory
    newOrder = (struct Orders *)malloc(sizeof(struct Orders));

    // Checks if there is already an order in the list. If not, adding it as first element
    newOrder->orderFloor = requestedFloor;
    newOrder->next = NULL;
    
    if (*head == NULL) {
        *head = newOrder
    } else {
        struct Orders* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // Adds the request to the next node after the last existing
        temp->next = newOrder;
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

void que_addOrder(struct Orders **hode, int order) {
    //struct Orders* new_Order = ();
};

void que_removeCompletedOrder(struct Orders);
void que_clearOrders(struct Orders);

