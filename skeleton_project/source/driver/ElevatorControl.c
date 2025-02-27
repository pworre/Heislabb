#include "elevatorControl.h"

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
