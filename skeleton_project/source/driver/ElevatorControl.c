#include "elevatorControl.h"
#include "elevio.h"

ElevatorState ctrl_getElevatorState(Elevator* anElevator) {
    return anElevator->state;
}
void ctrl_updateElevatorState(Elevator* anElevator, ElevatorState aState){
    anElevator->state = aState;
}

void ctrl_setFloor(Elevator* anElevator, int floor) {
    anElevator->lastFloor = floor;
}

void ctrl_startup(Elevator* anElevator) {
    elevio_motorDirection(DIRN_DOWN);
    if (elevio_floorSensor >= 0) {
        elevio_motorDirection(DIRN_STOP);
        ctrl_updateElevatorState(anElevator, STATIONARY);
        ctrl_setFloor(anElevator, elevio_floorsensor());
    }
}

void ctrl_run(Elevator* anElevator) {
    // Creates new and empty lists ready for orders
    struct Orders *orderHead = NULL;
    struct CabOrders *cabOrderHead = NULL;

    // Set state for running
    anElevator->run = 1;

    while (anElevator->run) {
        SM_updateElevatorState(&anElevator, &orderHead, &cabOrderHead);

        // BUTTONS: Scans continuosly for button inputs
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);

                // if button is from OUTSIDE of the cab
                if ((btnPressed == 1) && (b != BUTTON_CAB)) {
                    que_addOrder(&orderHead, f, b);
                // if the button is from INSIDE of the cab
                } else if (btnPressed == 1) {
                    que_addCabOrder(&cabOrderHead, f);
                }
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        que_checkQue(anElevator, &orderHead, &cabOrderHead);
    }
}

int nextDestination(Elevator* anElevator, Orders* order, CabOrders* cabOrder){
    if (anElevator->viabas == 1){
        return order->orderFloor;
    } else {
        return cabOrder->cabOrderFloor;
    }
}

/*
void nextDestination(Elevator* anElevator, Orders* order, CabOrders* cabOrder){
    if (anElevator->viabas == 1){
        anElevator->nextFloor = order->orderFloor;
    } else {
        anElevator->nextFloor = cabOrder->cabOrderFloor;
    }
}
*/