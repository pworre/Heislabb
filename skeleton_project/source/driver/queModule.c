#include "queModule.h"
#include "stdio.h"


void que_addOrder(struct Orders **head, int requestedFloor, ButtonType requestedDirection) {
    struct Orders *newOrder = NULL;
    // Saves the adress for Order-type in head and allocate memory. Using "struct Orders *" to convert from void * to struct-type
    newOrder = (struct Orders *)malloc(sizeof(struct Orders));

    // Checks if memory is allocated for the Orders-struct
    if (newOrder == NULL) {
        printf("Memory is not allocated for Orders");
    }

    // Checks if there is already an order in the list. If not, adding it as first element
    newOrder->orderFloor = requestedFloor;
    newOrder->orderDirection = requestedDirection;
    newOrder->next = NULL;
    
    if (*head == NULL) {
        *head = newOrder;
    } else {
        struct Orders* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // Adds the request to the next node after the last existing
        temp->next = newOrder;
    }
}

void que_checkViabas(struct Elevator* anElevator, struct Orders* que, struct CabOrders* cabOrder) {
        // Setting parameter if outside cab order is between elevator and cabOrder and goes in same direction
    if ((cabOrder->cabOrderFloor < que->next) && ((anElevator->state == MOVING_DOWN) && que->orderDirection == BUTTON_HALL_DOWN) || 
        (cabOrder->cabOrderFloor > que->next) && ((anElevator->state == MOVING_UP) && que->orderDirection == BUTTON_HALL_UP))  {
        anElevator->viabas = 1;
    } else {
        anElevator->viabas = 0;
    }
}

/* KOMMENTERT UT FOR Å PRØVE Å TILPASSE checkQue TIL CABORDER-rekkefølge
void que_checkQue(struct Elevator* anElevator, struct Orders* que, struct CabOrders* cabOrder) {
    if ((que->orderFloor < anElevator->lastFloor) && (anElevator->state != MOVING_UP)) {
        elevio_motorDirection(DIRN_DOWN);
        ctrl_updateElevatorState(anElevator, MOVING_DOWN);
    } else if ((que->orderFloor > anElevator->lastFloor) && (anElevator->state != MOVING_DOWN)) {
        elevio_motorDirection(DIRN_UP);
        ctrl_updateElevatorState(anElevator, MOVING_DOWN);
    }
}
*/

void que_checkQue(struct Elevator* anElevator, struct Orders* que, struct CabOrders* cabOrder) {
    if ((anElevator->nextFloor < anElevator->lastFloor) && (anElevator->state != MOVING_UP)) {
        elevio_motorDirection(DIRN_DOWN);
        ctrl_updateElevatorState(anElevator, MOVING_DOWN);
    } else if ((anElevator->nextFloor > anElevator->lastFloor) && (anElevator->state != MOVING_DOWN)) {
        elevio_motorDirection(DIRN_UP);
        ctrl_updateElevatorState(anElevator, MOVING_DOWN);
    }
}

void que_addOrder(struct Orders **hode, int order) {
    //struct Orders* new_Order = ();
};

void que_removeCompletedOrder(struct Orders);
void que_clearOrders(struct Orders);

void que_addCabOrder(struct CabOrders **head, int requestedFloor){
    struct Orders *newOrder = NULL;
    // Saves the adress for Order-type in head and allocate memory. Using "struct Orders *" to convert from void * to struct-type
    newOrder = (struct Orders *)malloc(sizeof(struct Orders));

    // Checks if memory is allocated for the Orders-struct
    if (newOrder == NULL) {
        printf("Memory is not allocated for Orders");
    }

    // Checks if there is already an order in the list. If not, adding it as first element
    newOrder->orderFloor = requestedFloor;
    newOrder->next = NULL;
    
    if (*head == NULL) {
        *head = newOrder;
    } else {
        struct Orders* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // Adds the request to the next node after the last existing
        temp->next = newOrder;
    }
}

