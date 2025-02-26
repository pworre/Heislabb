#include "queModule.h"
#include "stdlib.h"

void que_addOrder(struct Orders **hode, int orderToAdd) {
    struct Orders *head = NULL;
    // Saves the adress for Order-type in head and allocate memory
    head = (struct Orders *)malloc(sizeof(struct Orders));
    head->order_floor = orderToAdd;
    struct Orders* new_Order = ()
};

void que_removeCompletedOrder(struct Orders);
void que_clearOrders(struct Orders);