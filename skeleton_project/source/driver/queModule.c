#include "queModule.h"
#include "stdio.h"
#include "elevatorControl.h"


void que_addOrder(Orders **head, int requestedFloor, ButtonType requestedDirection) {
    // Check if the order already exists in the list
    Orders* temp = *head;
    while (temp != NULL) {
        if (temp->orderFloor == requestedFloor && temp->orderDirection == requestedDirection) {
            printf("Duplicate order: Floor %d, Direction %d already exists.\n", requestedFloor, requestedDirection);
            return; // Don't add the order if it's a duplicate
        }
        temp = temp->next;
    }

    // Allocate memory for the new order
    Orders* newOrder = (Orders *)malloc(sizeof(Orders));

    // Check if memory allocation was successful
    if (newOrder == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Set the new order's values
    newOrder->orderFloor = requestedFloor;
    newOrder->orderDirection = requestedDirection;
    newOrder->next = NULL;

    // If the list is empty, set the new order as the head
    if (*head == NULL) {
        *head = newOrder;
        printf("Added new order: Floor %d, Direction %d\n", requestedFloor, requestedDirection);
        return;
    }

    // If the list is not empty, traverse to the end and add the new order
    temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newOrder;
    printf("Added new order: Floor %d, Direction %d\n", requestedFloor, requestedDirection);
}

void que_printOrders(Orders *order) {
    if (order->next != NULL) {
        Orders *temp = order;
        while (temp->next != NULL) {
            printf("ETASJEBESTILLING    || Floor: %d, Direction: %d\n", temp->next->orderFloor, temp->next->orderDirection);
            temp = temp->next;
        }
    } else {
        printf("ETASJEBESTILLING    || Ingen aktive\n");
    }
    if (order->orderDirection == BUTTON_HALL_UP) {printf("ETASJEBESTILLING   || Kjører på bestilling OPP!\n");}
    else if (order->orderDirection == BUTTON_HALL_DOWN) {printf("ETASJEBESTILLING   || Kjører på bestilling NED!\n");}
}

void que_printCabOrders(CabOrders *cabOrder) {
    if (cabOrder->next != NULL) {
        CabOrders *temp = cabOrder;
        while (temp->next != NULL) {
            printf("CAB_BESTILLING      || Floor: %d\n", temp->next->cabOrderFloor);
            temp = temp->next;
        }
    } else {
        printf("CAB_BESTILLING      || Ingen aktive\n");
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

void que_checkQue(Elevator* anElevator, Orders* que, CabOrders* cabOrder) {
    // Sjekker at vi ikke har nullpekere
    if ((anElevator == NULL) || (que == NULL) || (cabOrder == NULL)) {
        printf("ERROR: Null-ptr detected in que_checkQue()!\n");
    }


    printf("Sjekker køen...");
    // Setting parameter if outside cab order is between elevator and cabOrder and goes in same direction
    if ((que->next != NULL) && (cabOrder->next != NULL)) {
        if (((cabOrder->next->cabOrderFloor < que->next->orderFloor) && ((anElevator->state == MOVING_DOWN) && que->orderDirection == BUTTON_HALL_DOWN)) || 
            ((cabOrder->next->cabOrderFloor > que->next->orderFloor) && ((anElevator->state == MOVING_UP) && que->orderDirection == BUTTON_HALL_UP)))  {
            anElevator->viabas = 1;
        }
    } else {
        anElevator->viabas = 0;
    }

    // Deciding the next destination
    if ((anElevator->nextFloor < anElevator->lastFloor) && (anElevator->state != MOVING_UP)) {
        elevio_motorDirection(DIRN_DOWN);
        ctrl_updateElevatorState(anElevator, MOVING_DOWN);
    } else if ((anElevator->nextFloor > anElevator->lastFloor) && (anElevator->state != MOVING_DOWN)) {
        elevio_motorDirection(DIRN_UP);
        ctrl_updateElevatorState(anElevator, MOVING_UP);
    } else {
        elevio_motorDirection(DIRN_STOP);
        ctrl_updateElevatorState(anElevator, STATIONARY);
    }
    
}


void que_removeCompletedOrder(Orders **orderHead){
    // Checks if there is nothing to remove
    if ((*orderHead == NULL) || ((*orderHead)->next == NULL)) {
        return;
    }

    elevio_buttonLamp((*orderHead)->orderFloor, (*orderHead)->orderDirection, 0);

    // Copying the pointer to the linkedlist and removing the first element
    Orders *temp = *orderHead;   // saves current order in temp-pointer
    *orderHead = (*orderHead)->next;    // points to next element in list
    free(temp);                         // deallocate memory

}


void que_clearOrders(Orders **head) {
    if (*head == NULL) {return;}

    Orders *current = (*head)->next;
    Orders *nextNode;
    

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    (*head)->next = NULL;
}


void que_clearCabOrders(CabOrders **head) {
    if (*head == NULL) {return;}

    CabOrders *current = (*head)->next;
    CabOrders *nextNode;
    

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    (*head)->next = NULL;
}



void que_addCabOrder(CabOrders **head, int requestedFloor) {
    // Check if the order already exists in the list
    CabOrders* temp = *head;
    while (temp != NULL) {
        if (temp->cabOrderFloor == requestedFloor) {
            printf("Duplicate order: Floor %d already exists.\n", requestedFloor);
            return; // Don't add the order if it's a duplicate
        }
        temp = temp->next;
    }

    // Allocate memory for the new order
    CabOrders* newOrder = (CabOrders *)malloc(sizeof(CabOrders));

    // Check if memory allocation was successful
    if (newOrder == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Set the new order's values
    newOrder->cabOrderFloor = requestedFloor;
    newOrder->next = NULL;

    // If the list is empty, set the new order as the head
    if (*head == NULL) {
        *head = newOrder;
        printf("Added new order: Floor %d\n", requestedFloor);
        return;
    }

    // If the list is not empty, traverse to the end and add the new order
    temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newOrder;
    printf("Added new order: Floor %d\n", requestedFloor);
}

void que_removeCompleteCabdOrder(Elevator *anElevator, Orders *order, CabOrders **orderHead){
    // Checks if there is nothing to remove
    if ((*orderHead == NULL) && ((*orderHead)->next == NULL)) {
        return;
    }

    elevio_buttonLamp((*orderHead)->cabOrderFloor, BUTTON_CAB, 0);

    /*
    // Copying the pointer to the linkedlist and removing the first element
    CabOrders *temp = *orderHead;   // saves current order in temp-pointer
    *orderHead = (*orderHead)->next;    // points to next element in list
    free(temp);                         // deallocate memory
    */

   CabOrders *prev = *orderHead;
   CabOrders *current = prev->next;

   while(current != NULL) {
        if (current->cabOrderFloor == que_nextCabOrder(anElevator, *orderHead, order)) {
            if (current->next != NULL) {
                prev->next = current->next;
                free(current);
                return;           
            } else {
                prev->next = NULL;
                free(current);
                return;
            }
            printf("------------    DELETED A CABORDER  ------------!\n");
        }
        current = prev->next;     
   }

}


int que_nextCabOrder(Elevator *anElevator, CabOrders *orderHead, Orders *outsideOrder) {
    if ((orderHead == NULL) || ((orderHead)->next == NULL)) {
        return -2;
    }

    //CabOrders *prev = *orderHead;
    CabOrders *current = orderHead->next;
    ButtonType directionOrdered = outsideOrder->orderDirection; // Bruker første node siden den er den som kjøres på (IKKE TIL!)
    int floorToReturn_UP = 5;
    int floorToReturn_DOWN = -1;


    while (current != NULL) {
        if ((directionOrdered == BUTTON_HALL_UP) && (anElevator->lastFloor <= current->cabOrderFloor)) {
            if (current->cabOrderFloor < floorToReturn_UP) {
                floorToReturn_UP = current->cabOrderFloor;
            } 
        } else if ((directionOrdered == BUTTON_HALL_DOWN) && (anElevator->lastFloor >= current->cabOrderFloor)) {
            if (current->cabOrderFloor > floorToReturn_DOWN) {
                floorToReturn_DOWN = current->cabOrderFloor;
            } 
        }
        current = current->next;
    }

    if (floorToReturn_UP != 5) {
        return floorToReturn_UP;
    } else if (floorToReturn_DOWN != -1) {
        return floorToReturn_DOWN;
    } else {
        return -2;
    }
}