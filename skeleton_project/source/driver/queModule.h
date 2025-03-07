#pragma once
#include "elevio.h"

/**
* @file
* @brief A simple library for que-control of the elevator. 
* Using a linked list to have control of the que of the orders. 
* Functions in order to add, remove and check the que. 
*/

// Forward-declaration
typedef struct ElevatorTag Elevator;

// Linked list for que-system
typedef struct OrderTag {
    int orderFloor;
    ButtonType orderDirection;

    // Self-referential structure pointing to next the order and info about the next order
    struct OrderTag *next;
} Orders;



typedef struct CabOrderTag {
    int cabOrderFloor;

    struct CabOrderTag *next;
} CabOrders;

void que_printOrders(Orders *order);
void que_printCabOrders(CabOrders *cabOrder);

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
void que_addOrder(Orders **head, int requestedFloor, ButtonType requestedDirection);



/**
* @brief Checking the que and compares the current floor of the elevator and the next floor
* according to the que-list. This for setting the motor direction and updating states. 
*
* @param[in] anElevator Pointer to the Elevator-struct to have access to elevator's last position and setting motor direction.
* @param[in] que Pointer to the que of the elevator's orders. 
* @param[in] cabOrder Pointer to the que of the elevator's orders from inside of cab. 
*
* @return nothing. Sets the @p MotorDirection and updates the elevator state. 
*/
void que_checkQue(Elevator* anElevator, Orders* que, CabOrders* cabOrder);



/**
* @brief A function for removing completed orders from outside of cab. 
*
* @param[in] orderHead Pointer to the que of the elevator's orders. 
*
* @return nothing. Sets @p orderHead pointing to next element and deallocating
*/
void que_removeCompletedOrder(Orders** orderHead);



void que_clearOrders(Orders **head);


void que_clearCabOrders(CabOrders **head);



void que_addCabOrder(CabOrders **head, int requestedFloor);



/**
* @brief A function for removing completed orders from inside of the cab. 
*
* @param[in] orderHead Pointer to the que of the elevator's orders. 
*
* @return nothing. Sets @p orderHead pointing to next element and deallocating
*/
void que_removeCompleteCabdOrder(Elevator *anElevator, Orders *order, CabOrders **orderHead);




int que_nextCabOrder(Elevator *anElevator, CabOrders *orderHead, Orders *outsideOrder);