#pragma once
#include "elevio.h"
#include "elevatorControl.h"
#include "queModule.h"

/**
* @file
* @brief A simple library for stateMachine containing
*functions and variabler for describing the current
*state of the elevator.
*/

#ifndef ELEVATOR_STATE_H
#define ELEVATOR_STATE_H

typedef enum ElevatorStateTag{ 
    MOVING_DOWN   = 0,
    STATIONARY   = 1,
    MOVING_UP     = 2
} ElevatorState;

#endif

/**
* @brief Function for updating the state-values for the elevator
*
* @param[in] anElevator Pointer to the Elevator-struct to have access to information about the last floors for elevators. 
* @param[in] order Pointer to the que of the elevator from outside at floors
* @param[in] cabOrder Pointer to the que of the elevator's orders from inside the cab
*
* @return nothing. Sets the current and next floor for the elevator
*/
void SM_updateElevatorState(Elevator *anElevator, Orders *order, CabOrders *cabOrder);

int SM_lastFloor(Elevator *anElevator);

/**
* @brief Function for startup procecure for the elevator
*
* @param[in] anElevator Pointer to the Elevator-struct to have access to information about the last floors for elevators. 
*
* @return @p nextFloor. Int type for next floor using to set stateParameter.
*/
int SM_nextDestination(Elevator* anElevator, Orders* order, CabOrders* cabOrder);
