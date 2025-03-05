#include "elevatorStateMachine.h"

void SM_updateElevatorState(Elevator *anElevator, Orders *order, CabOrders *cabOrder){
    anElevator->lastFloor = elevio_floorSensor();
    anElevator->nextFloor = nextDestination(&anElevator, &order, &cabOrder);
}