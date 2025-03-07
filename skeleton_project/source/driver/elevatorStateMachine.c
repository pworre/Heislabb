#include "elevatorStateMachine.h"

void SM_updateElevatorState(Elevator *anElevator, Orders *order, CabOrders *cabOrder){
    anElevator->lastFloor = SM_lastFloor(anElevator);
    anElevator->nextFloor = SM_nextDestination(anElevator, order, cabOrder);
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

/*int SM_nextDestination(Elevator* anElevator, Orders* order, CabOrders* cabOrder){
    int nextCaborder;
    int floorToCompare;

    if (order->next != NULL) {
        if ((anElevator->viabas == 1) || (cabOrder->next == NULL)) {
            return order->next->orderFloor;
        } 
    }
    if (cabOrder->next != NULL){
        nextCaborder = cabOrder->next->cabOrderFloor;
        if ((anElevator->viabas == 0) || (order->next == NULL)) {
            if (order->orderDirection == BUTTON_HALL_UP) {
                CabOrders *tempCabOrder = cabOrder->next;
                while (tempCabOrder->next != NULL) {
                    floorToCompare = tempCabOrder->next->cabOrderFloor;
                    if ((floorToCompare < nextCaborder) && (floorToCompare >= anElevator->lastFloor)) {
                        nextCaborder = floorToCompare;
                    }
                    tempCabOrder = tempCabOrder->next;
                }
            } else if (order->orderDirection == BUTTON_HALL_DOWN) {
                CabOrders *tempCabOrder = cabOrder->next;
                while (tempCabOrder->next != NULL) {
                    floorToCompare = tempCabOrder->next->cabOrderFloor;
                    if ((floorToCompare > nextCaborder) && (floorToCompare <= anElevator->lastFloor)) {
                        nextCaborder = floorToCompare;
                    }
                    tempCabOrder = tempCabOrder->next;
                } 
            }

            return nextCaborder;
        }
    }
    return anElevator->lastFloor;
}*/

int SM_nextDestination(Elevator* anElevator, Orders* order, CabOrders* cabOrder) {
    int nextCaborder;
    int floorToCompare;

    // If there are hall orders, prioritize them
    if (order != NULL && order->next != NULL) {
        if ((anElevator->viabas == 1) || (cabOrder == NULL || cabOrder->next == NULL)) {
            return order->next->orderFloor;
        } 
    }

    // If there are cab orders, check them
    if (cabOrder != NULL && cabOrder->next != NULL) {
        nextCaborder = cabOrder->next->cabOrderFloor; // Initialize with first found cab order

        if (order != NULL && order->orderDirection == BUTTON_HALL_UP) {
            CabOrders *tempCabOrder = cabOrder->next;
            while (tempCabOrder != NULL) {  // Iterate all cab orders
                floorToCompare = tempCabOrder->cabOrderFloor;
                if ((floorToCompare >= anElevator->lastFloor) && ((nextCaborder > anElevator->lastFloor) ? (floorToCompare < nextCaborder) : 1)) {
                    nextCaborder = floorToCompare;
                }
                tempCabOrder = tempCabOrder->next;
            }
        } else if (order != NULL && order->orderDirection == BUTTON_HALL_DOWN) {
            CabOrders *tempCabOrder = cabOrder->next;
            while (tempCabOrder != NULL) {
                floorToCompare = tempCabOrder->cabOrderFloor;
                if ((floorToCompare <= anElevator->lastFloor) && ((nextCaborder < anElevator->lastFloor) ? (floorToCompare > nextCaborder) : 1)) {
                    nextCaborder = floorToCompare;
                }
                tempCabOrder = tempCabOrder->next;
            } 
        }

        return nextCaborder;
    }

    return anElevator->lastFloor; // Default return value if no orders exist
}
