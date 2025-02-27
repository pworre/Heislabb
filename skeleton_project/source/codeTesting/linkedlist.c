#include "linkedlist.h"


void add_linkedlist(struct Orders **head, int requestedFloor) {
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


void print_linkedlist(struct Orders *head) {
    struct Orders *temp = head;
    
    printf("Orders in the queue:\n");
    while (temp != NULL) {
        printf("Floor: %d\n", temp->orderFloor);
        temp = temp->next;
    }
}