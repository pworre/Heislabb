#pragma once

#include "elevatorStateMachine.h"
#include "elevio.h"
#include "queModule.h"
#include "stdlib.h"

/**
* @file
* @brief A simple library for struct Elevator and
* and control function for the elevator. 
*/

struct Elevator {
    ElevatorState state;
    int lastFloor;
    int run;
    int viabas;             // variable which is 1 if the elevator will stop on either way for bringing more PAX
    int nextFloor;
};

ElevatorState ctrl_getElevatorState(struct Elevator* anElevator);
void ctrl_updateElevatorState(struct Elevator* anElevator, ElevatorState aState);
void ctrl_setFloor(struct Elevator* anElevator, int floor);

void ctrl_startup(struct Elevator* anElevator);
void ctrl_run(struct Elevator* anElevator, struct Orders* order, struct CabOrders* cabOrder);

/**
* @brief Function for 
*
* @param[in] anElevator Pointer to the Elevator-struct to have access to information if stop viabas and bring more PAX
* @param[in] order Pointer to the que of the elevator from outside at floors
* @param[in] cabOrder Pointer to the que of the elevator's orders from inside the cab
* @param[out] que int with value equal to the next
*
* @return nothing. Sets the @p MotorDirection and updates the elevator state. 
*/
void nextDestination(struct Elevator* anElevator, struct Orders* order, struct CabOrders* cabOrder);