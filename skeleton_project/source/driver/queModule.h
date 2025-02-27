#pragma once
#include "elevatorControl.h"
#include "elevio.h"
/**
* @file
* @brief A simple library for que-control of the elevator. 
* Using a linked list to have control of the que of the orders. 
* Functions in order to add, remove and check the que. 
*/

// Linked list for que-system
struct Orders {
    int orderFloor;
    ButtonType orderDirection;

    // Self-referential structure pointing to next the order and info about the next order
    struct Orders *next;
};

struct CabOrders {
    int cabOrderFloor;

    struct CabOrders *next;
};



/**
* @brief Adding new orders to a linkedlist of a struct Orders.
*
* @param[in] head doublepointer to the ehad of the linked list. Necessary in order to change the list.
* @param[in] requestedFloor The requested floor from customer using the elevator.
* @param[in] requestedDirection The requested floor from customer using the elevator.
*
* @return nothing. The @p head modifies the list by adding a new node. 
* Last element in the list contains @c NULL pointer in @p next.
*/
void que_addOrder(struct Orders **head, int requestedFloor, ButtonType requestedDirection);


/**
* @brief Checking the que and compares the current floor of the elevator and the next floor
* according to the que-list. This for setting the motor direction and updating states. 
*
* @param[in] anElevator Pointer to the Elevator-struct to have access to elevator's last position and setting motor direction.
* @param[in] que Pointer to the que of the elevator's orders. 
*
* @return nothing. Sets the @p MotorDirection and updates the elevator state. 
*/
void que_checkQue(struct Elevator* anElevator, struct Orders* que, struct CabOrders* cabOrder);


void que_removeCompletedOrder(struct Orders);
void que_clearOrders(struct Orders);

void que_addCabOrder(struct CabOrders **head, int requestedFloor);