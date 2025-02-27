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

void ctrl_run(struct Elevator* anElevator, struct Orders* order) {
    struct Orders *orderHead = NULL;

    while (anElevator->run) {
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if (btnPressed == 1) {
                    que_addOrder(orderHead, f, b);
                }
                elevio_buttonLamp(f, b, btnPressed);
            }
        }
    }
}