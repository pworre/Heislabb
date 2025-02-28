#include "elevatorControl.h"
#include "elevio.h"

ElevatorState ctrl_getElevatorState(struct Elevator* anElevator) {
    return anElevator->state;
}
void ctrl_updateElevatorState(struct Elevator* anElevator, ElevatorState aState){
    anElevator->state = aState;
}

void ctrl_setFloor(struct Elevator* anElevator, int floor) {
    anElevator->lastFloor = floor;
}

void ctrl_startup(struct Elevator* anElevator) {
    elevio_motorDirection(DIRN_DOWN);
    if (elevio_floorSensor >= 0) {
        elevio_motorDirection(DIRN_STOP);
        ctrl_updateElevatorState(anElevator, STATIONARY);
        ctrl_setFloor(anElevator, elevio_floorsensor());
    }
}

void ctrl_run(struct Elevator* anElevator, struct Orders* order, struct CabOrders* cabOrder) {
    // Creates new and empty lists ready for orders
    struct Orders *orderHead = NULL;
    struct CabOrders *cabOrderHead = NULL;


    while (anElevator->run) {
        // Scans continuosly for button inputs
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);

                // if button is from OUTSIDE of the cab
                if ((btnPressed == 1) && (b != BUTTON_CAB)) {
                    que_addOrder(orderHead, f, b);
                // if the button is from INSIDE of the cab
                } else if (btnPressed == 1) {
                    que_addCabOrder(cabOrderHead, f);
                }
                elevio_buttonLamp(f, b, btnPressed);
            }
        }
        // bruker viabas her for å sjekke om stoppe på veien
        que_checkViabas(anElevator, order,cabOrder);
    }
}

void nextDestination(struct Elevator* anElevator, struct Orders* order, struct CabOrders* cabOrder){
    if (anElevator->viabas == 1){
        anElevator->nextFloor = order->orderFloor;
    } else {
        anElevator->nextFloor = cabOrder->cabOrderFloor;
    }
}