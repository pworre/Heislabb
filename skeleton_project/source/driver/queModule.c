#include "queModule.h"
#include "stdio.h"
#include "elevatorControl.h"


void que_addOrder(Orders **head, int requestedFloor, ButtonType requestedDirection) {
    //Orders *newOrder = NULL;
    // Saves the adress for Order-type in head and allocate memory. Using "struct Orders *" to convert from void * to struct-type
    Orders *newOrder = (Orders *)malloc(sizeof(Orders));

    // Checks if memory is allocated for the new Orders-struct
    if (newOrder == NULL) {
        printf("Memory is not allocated for Orders");
        return;
    }

    // Checks if there is already an order in the list. If not, adding it as first element
    newOrder->orderFloor = requestedFloor;
    newOrder->orderDirection = requestedDirection;
    newOrder->next = NULL;
    
    if (*head == NULL) {
        *head = newOrder;
        return; // Returns if the list is empty and added the neweOrder
    } else {
        Orders* temp = *head;
        while ((temp->next != NULL) && (temp != NULL)) {
            temp = temp->next;
        }
        
        // Adds the request to the next node after the last existing
        temp->next = newOrder;
    }
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
        if (((cabOrder->next->cabOrderFloor < que->next->orderFloor) && ((anElevator->state == MOVING_DOWN) && (que->next->orderDirection == BUTTON_HALL_DOWN))) || 
            ((cabOrder->next->cabOrderFloor > que->next->orderFloor) && ((anElevator->state == MOVING_UP) && (que->next->orderDirection == BUTTON_HALL_UP))))  {
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
    //Orders *newOrder = NULL;
    // Saves the adress for Order-type in head and allocate memory. Using "struct Orders *" to convert from void * to struct-type
    CabOrders *newOrder = (CabOrders *)malloc(sizeof(CabOrders));

    // Checks if memory is allocated for the new Orders-struct
    if (newOrder == NULL) {
        printf("Memory is not allocated for Orders");
    }

    // Checks if there is already an order in the list. If not, adding it as first element
    newOrder->cabOrderFloor = requestedFloor;
    newOrder->next = NULL;
    
    if (*head == NULL) {
        *head = newOrder;
        return; // Returns if the list is empty and added the neweOrder
    } else {
        CabOrders* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        
        // Adds the request to the next node after the last existing
        temp->next = newOrder;
    }
}

/*void que_removeCompleteCabdOrder(Elevator *anElevator, CabOrders **orderHead){
    // Checks if there is nothing to remove
    if ((*orderHead == NULL) || ((*orderHead)->next == NULL)) {
        return;
    }

    elevio_buttonLamp((*orderHead)->cabOrderFloor, BUTTON_CAB, 0);

      GAMMEL REMOVE!!!!!
    // Copying the pointer to the linkedlist and removing the first element
    CabOrders *temp = *orderHead;   // saves current order in temp-pointer
    *orderHead = (*orderHead)->next;    // points to next element in list
    free(temp);                         // deallocate memory
    


   // Checks if there is more than 2 caborders to avoid SEGV-fault
    CabOrders *prev = *orderHead;   // saves current order in temp-pointer
    CabOrders *current = prev->next;


    // If removing element 2
    while (current != NULL) {
        printf("DELETING: sjekker om mer enn 2 elementer\n");
        if ((current->cabOrderFloor == anElevator->nextFloor) && (anElevator->lastFloor == anElevator->nextFloor) && (current->next != NULL)) {
            // connecting node 1 to node 3
            prev->next = current->next;
            free(current);
            current = prev->next;
            printf("DELETING: Fjernet en node midt i :))\n");
        } else if (((current->cabOrderFloor == anElevator->nextFloor) && (anElevator->lastFloor == anElevator->nextFloor)) && (current->next == NULL)) {
            free(current);
            prev->next = NULL;
        } else if (!((current->cabOrderFloor == anElevator->nextFloor) && (anElevator->lastFloor == anElevator->nextFloor)) && (current->next == NULL)) {
            prev->next = NULL;
        } else {
            prev = current;
            current = current->next;
        }
    }*/

/*
void que_removeCompleteCabdOrder(Elevator *anElevator, CabOrders **orderHead) {
    // Ensure list is valid and has at least two elements
    if ((*orderHead == NULL) || ((*orderHead)->next == NULL)) {
        return;
    }

    elevio_buttonLamp((*orderHead)->cabOrderFloor, BUTTON_CAB, 0);

    CabOrders *current = (*orderHead)->next;  // Start from second node
    CabOrders *prev = *orderHead;  // First node is not removed

    // Iterate over the list
    while (current != NULL) {
        printf("DELETING: sjekker om mer enn 2 elementer\n");

        // If the current node matches the elevator's next floor, remove it
        if ((current->cabOrderFloor == anElevator->nextFloor) && (anElevator->lastFloor == anElevator->nextFloor)) {
            prev->next = current->next;  // Bypass current node
            free(current);  // Free memory
            current = prev->next;  // Move to the next node
        } else {
            prev = current;  // Move prev forward
            current = current->next;  // Move current forward
        }
    }
}*/

void que_removeCompleteCabdOrder(Elevator *anElevator, CabOrders **orderHead) {
    CabOrders *current = *orderHead;
    CabOrders *prev = NULL;

    // Handle the case where the head itself has the specific value
    while ((current != NULL) && ((current->cabOrderFloor == anElevator->nextFloor) && (anElevator->lastFloor == anElevator->nextFloor))) {
        (*orderHead) = current->next;  // Move the head to the next node
        free(current);           // Free the current node
        current = (*orderHead);         // Move current to the next node
    }

    // Now handle the case where nodes after the head have the specific value
    while (current != NULL) {
        while ((current != NULL) && ((current->cabOrderFloor == anElevator->nextFloor) && (anElevator->lastFloor == anElevator->nextFloor))) {
            prev = current;
            current = current->next;
        }
        // If we found a node with the specific value
        if (current != NULL) {
            prev->next = current->next; // Bypass the current node
            free(current);               // Free the current node
            current = prev->next;        // Move current to the next node
        }
    }
}

/*
void que_removeFloorCabOrder(Elevator *anElevator, CabOrders **orderHead, int floorToRemove) {
    CabOrders *prev = *orderHead;
    CabOrders *current = prev->next;

    while (current != NULL) {
        while (current->cabOrderFloor == floorToRemove) {
            if (current->next == NULL) {
                free(current);
                prev->next == NULL;
                return;
            } else {
                current = current->next;
                free(prev->next);
            }
        }
        prev->next = current;
    }
}*/