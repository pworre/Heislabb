#pragma once
#include "stdio.h"
#include "stdlib.h"

// Linked list for que-system
struct Orders {
    int orderFloor;

    // Self-referential structure pointing to next the order and info about the next order
    struct Orders *next;
};

void add_linkedlist(struct Orders **head, int requestedFloor);

void print_linkedlist(struct Orders *head);