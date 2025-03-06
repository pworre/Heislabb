#include "elevatorStateMachine.h"

void SM_updateElevatorState(Elevator *anElevator, Orders *order, CabOrders *cabOrder){
    anElevator->lastFloor = SM_lastFloor(anElevator);
    anElevator->nextFloor = SM_nextDestination(anElevator, order, cabOrder);
}

int SM_lastFloor(Elevator *anElevator){
    int currentFloor = elevio_floorSensor();
    if ((anElevator->lastFloor != currentFloor) && (currentFloor != -1)){
        return currentFloor;
    } else {
        return anElevator->lastFloor;
    }
}

int SM_nextDestination(Elevator* anElevator, Orders* order, CabOrders* cabOrder){
    if (order->next != NULL) {
        if ((anElevator->viabas == 1) || (cabOrder->next == NULL)) {
            return order->next->orderFloor;
        } 
    }
    if (cabOrder->next != NULL){
        if ((anElevator->viabas == 0) || (order->next == NULL))
            return cabOrder->next->cabOrderFloor;
    } else {
        return anElevator->lastFloor;
    }
}
