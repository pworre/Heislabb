#pragma once
#include "elevio.h"
#include "elevatorStateMachine.h"
#include "queModule.h"
#include "stdlib.h"
#include "lightModule.h"
#include "time.h"

/**
* @file
* @brief A simple library for struct Elevator and
* and control function for the elevator. 
*/
#ifndef ELEVATOR_H
#define ELEVATOR_H

typedef struct {
    ElevatorState state;
    int lastFloor;
    int run;
    int viabas;             // variable which is 1 if the elevator will stop on either way for bringing more PAX
    int nextFloor;
} Elevator;

#endif

ElevatorState ctrl_getElevatorState(Elevator* anElevator);



void ctrl_updateElevatorState(Elevator* anElevator, ElevatorState aState);

/**
* @brief Function for startup procecure for the elevator
*
* @param[in] anElevator Pointer to the Elevator-struct to have access to information about the last floors for elevators. 
*
* @return nothing. Runs the elevator to a floor before running normal program. 
*/
void ctrl_startup(Elevator* anElevator);

/**
* @brief Function for running the normal operating program for the elevator
*
* @param[in] anElevator Pointer to the Elevator-struct to have access to information of the elevator states. 
*
* @return nothing. Runs the operating program for the elevator. 
*/
void ctrl_run(Elevator* anElevator);



/**
* @brief Function for scanning button inputs and adding orders to the linkedlist
*
* @param[in] anElevator Pointer to the Elevator-struct to have access to information if stop viabas and bring more PAX
* @param[in] order Pointer to the que of the elevator from outside at floors
* @param[in] cabOrder Pointer to the que of the elevator's orders from inside the cab
*
* @return nothing. The orders are added to the linkedlists
*/
void ctrl_scanButtonInputs(Elevator *anElevator, Orders *orderHead, CabOrders *cabOrderHead);
