#include "elevatorStateMachine.h"

void SM_updateElevatorState(Elevator *anElevator, Orders *order, CabOrders *cabOrder){
    anElevator->lastFloor = SM_lastFloor(anElevator);
    
    if (order->next != NULL) {
        anElevator->nextOutsideOrder_floor = order->next->orderFloor;
        anElevator->nextOutsideOrder_dir = order->next->orderDirection;
    } else {
        anElevator->nextOutsideOrder_floor = -1;    // Setting -1 for indicator for no active OutsideOrders
    }

    anElevator->nextCabOrder = que_nextCabOrder(anElevator, cabOrder, order);
    anElevator->nextFloor = SM_nextDestination(anElevator);
}

int SM_lastFloor(Elevator *anElevator){
    int currentFloor = elevio_floorSensor();
    if ((anElevator->lastFloor != currentFloor) && (currentFloor != -1)){
        elevio_floorIndicator(currentFloor);
        return currentFloor;
    } else {
        return anElevator->lastFloor;
    }
}

/*
int SM_nextDestination(Elevator* anElevator){
    if ((anElevator->viabas == 1) || (anElevator->nextCabOrder == -1)) {
        if (anElevator->nextOutsideOrder_floor != -1) {
            return anElevator->nextOutsideOrder_floor;            
        }
    } else if ((anElevator->viabas == 0) || (anElevator->nextOutsideOrder_floor == -1)) {
        if (anElevator->nextCabOrder != -1){
            return anElevator->nextCabOrder;            
        }
    }
    return anElevator->lastFloor;
}
*/

int SM_nextDestination(Elevator* anElevator){
    if (anElevator->viabas == 1) {  // Prioritize outside orders
        if (anElevator->nextOutsideOrder_floor != -1) {
            return anElevator->nextOutsideOrder_floor;
        }
    }
    
    if (anElevator->nextCabOrder != -1) {  // Always serve cab orders if they exist
        return anElevator->nextCabOrder;
    }

    if (anElevator->nextOutsideOrder_floor != -1) {  // If still available, serve outside orders
        return anElevator->nextOutsideOrder_floor;
    }

    return anElevator->lastFloor;  // No orders, stay put
}
