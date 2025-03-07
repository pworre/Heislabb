#include <stdio.h>
#include <time.h>
#include "elevio.h"
#include "elevatorStateMachine.h"
#include "elevatorControl.h"
#include "queModule.h"

void door_open(Elevator *anElevator, Orders *orderHead, CabOrders *cabOrderHead, int lastStop, int stopValue);