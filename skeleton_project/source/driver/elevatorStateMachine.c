#include "elevatorStateMachine.h"

void SM_updateElevatorState(Elevator *anElevator, Orders *order, CabOrders *cabOrder){
    anElevator->lastFloor = elevio_floorSensor();
    anElevator->nextFloor = nextDestination(&anElevator, &order, &cabOrder);
}

int SM_nextDestination(Elevator* anElevator, Orders* order, CabOrders* cabOrder){
    if (anElevator->viabas == 1){
        return order->orderFloor;
    } else {
        return cabOrder->cabOrderFloor;
    }
}
