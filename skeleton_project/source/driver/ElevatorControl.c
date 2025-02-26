#include "elevatorControl.h"

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
