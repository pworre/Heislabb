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
    printf("FloorSensor: %d\n", elevio_floorSensor());

    // elevio_floorSensor() gives output -1 when not receiving any information
    while (elevio_floorSensor() == -1) {
        elevio_motorDirection(DIRN_DOWN);
        //printf("FloorSensor: %d\n", elevio_floorSensor());
        /*
        if (elevio_floorSensor() >= 0) {
            elevio_motorDirection(DIRN_STOP);
            ctrl_updateElevatorState(anElevator, STATIONARY);
            anElevator->lastFloor = elevio_floorSensor();
        }
        */
    }
    anElevator->lastFloor = elevio_floorSensor();
    elevio_motorDirection(DIRN_STOP);
    printf("Gitt startposisjon er: %d\n", anElevator->lastFloor);
}

void ctrl_run(Elevator* anElevator) {
    printf("Startet på ctrl_run()!\n");

    // Creates new and empty lists ready for orders
    Orders *orderHead = malloc(sizeof(Orders));
    CabOrders *cabOrderHead = malloc(sizeof(CabOrders));
    if ((orderHead == NULL) || (cabOrderHead == NULL)) {
        printf("FEIL: Kunne ikke allokere minne til CabOrder eller Order!\n");
    }
    printf("Minnet allokert til Orders og CabOrders\n");


    // Sjekker om anElevator riktig allokert innad i run
    if (anElevator != NULL) {
        printf("anElevator er vellykka innad i run :)\n");
    }
    

    // Set state for running
    anElevator->run = 1;

    while (1) {
        printf("entret while-løkke");
        SM_updateElevatorState(anElevator, orderHead, cabOrderHead);

        // BUTTONS: Scans continuosly for button inputs
        ctrl_scanButtonInputs(anElevator, orderHead, cabOrderHead);

        // Troubleshooting
        que_addOrder(&orderHead, anElevator->lastFloor, BUTTON_HALL_UP);

        // DOOR_OPEN functionality
        if ((anElevator->state != STATIONARY) && (anElevator->lastFloor == anElevator->nextFloor)) {
            elevio_motorDirection(DIRN_STOP);
            anElevator->state = STATIONARY;
            lgt_setLight(LIGHT_DOOR_OPEN, 1);

            // 3 sekunder ventetid
            clock_t start_time = clock();
            double seconds_passed = 0;
            while(seconds_passed < 3.0) {
                seconds_passed = (double)(clock() - start_time) / CLOCKS_PER_SEC;

                // Sjekke for bestillinger under ventetid
                ctrl_scanButtonInputs(anElevator, orderHead, cabOrderHead);

                // Obstruksjonsfunksjonalitet
                //
                //
            }

            lgt_setLight(LIGHT_DOOR_OPEN, 0);
        }

        que_checkQue(anElevator, orderHead, cabOrderHead);
    }

    // Deallokerer minnet
    free(orderHead);
    free(cabOrderHead);
}

void ctrl_scanButtonInputs(Elevator *anElevator, Orders *orderHead, CabOrders *cabOrderHead){
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
