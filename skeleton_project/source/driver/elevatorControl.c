#include "elevatorControl.h"



ElevatorState ctrl_getElevatorState(Elevator* anElevator) {
    return anElevator->state;
}
void ctrl_updateElevatorState(Elevator* anElevator, ElevatorState aState){
    anElevator->state = aState;
}

void ctrl_startup(Elevator* anElevator) {
    // Skrur av alle lys hvis noen var på
    for(int f = 0; f < N_FLOORS; f++){
        elevio_buttonLamp(f, BUTTON_HALL_DOWN, 0);
        elevio_buttonLamp(f, BUTTON_HALL_UP, 0);
        elevio_buttonLamp(f, BUTTON_CAB, 0);
    }


    printf("------------------    W E L C O M E     T O     T H I S     E L E V A T O R    ------------------\n\n");

    // elevio_floorSensor() gives output -1 when not receiving any information
    while (elevio_floorSensor() == -1) {
        elevio_motorDirection(DIRN_DOWN);
    }
    anElevator->lastFloor = elevio_floorSensor();
    elevio_motorDirection(DIRN_STOP);
    printf("Startposition: %d\n", anElevator->lastFloor);
    //anElevator->nextCabOrder = -1;
    //anElevator->nextOutsideOrder_floor = -1;
    //anElevator->nextOutsideOrder_dir = BUTTON_HALL_UP;
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

    orderHead->orderFloor = anElevator->lastFloor;
    orderHead->orderDirection = BUTTON_HALL_UP;
    orderHead->next = NULL;

    cabOrderHead->cabOrderFloor = anElevator->lastFloor;
    cabOrderHead->next = NULL;
    int lastStopValue = -1;
    int stopValueInt = 0;
    int *lastStop = &lastStopValue;
    int *stopValue = &stopValueInt;


    // Sjekker om anElevator riktig allokert innad i run
    if (anElevator != NULL) {
        printf("anElevator er vellykka innad i run :)\n");
    }
    

    // Set state for running
    anElevator->run = 1;

    while (anElevator->run) {
        
        if ((anElevator != NULL) && (orderHead != NULL) && (cabOrderHead != NULL)) {
            SM_updateElevatorState(anElevator, orderHead, cabOrderHead);
        }

        que_printOrders(orderHead);
        que_printCabOrders(cabOrderHead);

        // BUTTONS: Scans continuosly for button inputs
        ctrl_scanButtonInputs(anElevator, orderHead, cabOrderHead);

        // STOP-FUNCTION
        *stopValue = elevio_stopButton();
        if (*stopValue == 1) {
            ctrl_stop(anElevator, orderHead, cabOrderHead, stopValue);
        }

        if (orderHead->next != NULL) {
            if ((anElevator->lastFloor == anElevator->nextOutsideOrder_floor) && (anElevator->nextFloor != anElevator->nextCabOrder)) {
                que_removeCompletedOrder(&orderHead);
            }
        }
        if ((cabOrderHead->next != NULL) && (anElevator->nextCabOrder == anElevator->lastFloor) && (anElevator->nextCabOrder != -1)) {
            que_removeCompleteCabdOrder(anElevator, orderHead, &cabOrderHead);
        }
    
        door_open(anElevator, orderHead, cabOrderHead, lastStop, stopValue);

        printf("FLOORSENSOR: %d         //      LASTFLOOR: %d\n", elevio_floorSensor(), anElevator->lastFloor);
        que_checkQue(anElevator);

        printf("NEXT FLOOR: %d\n", anElevator->nextFloor);
        printf("NEXT CABFLOOR: %d\n", que_nextCabOrder(anElevator, cabOrderHead, orderHead));
    }

    // Deallokerer minnet
    free(orderHead);
    free(cabOrderHead);
}

void ctrl_scanButtonInputs(Elevator *anElevator, Orders *orderHead, CabOrders *cabOrderHead){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);

            if (btnPressed) {
                // if button is from OUTSIDE of the cab
                if (b != BUTTON_CAB) {
                    que_addOrder(&orderHead, f, b);
                // if the button is from INSIDE of the cab
                } else {
                    que_addCabOrder(&cabOrderHead, f);
                }
                if((f != anElevator->lastFloor) || (anElevator->nextOutsideOrder_floor != f)){
                    elevio_buttonLamp(f, b, btnPressed);                    
                }
            }
        }
    }
}

void ctrl_stop(Elevator *anElevator, Orders *orderHead, CabOrders *cabOrderHead, int *value) {
    while(*value == 1) {
        ElevatorState prev_state = anElevator->state;
        anElevator->state = STATIONARY;
        elevio_stopLamp(1);
        elevio_motorDirection(DIRN_STOP);
        que_clearOrders(&orderHead);
        que_clearCabOrders(&cabOrderHead);

        if (prev_state == MOVING_UP) {
            anElevator->lastFloor = elevio_floorSensor();
        } else {
            anElevator->lastFloor = (anElevator->lastFloor)+1;
        }
        anElevator->nextFloor = elevio_floorSensor();
        

        if(elevio_floorSensor() != -1) {
            elevio_doorOpenLamp(1);
        }
        *value = elevio_stopButton();
    }

    elevio_stopLamp(0);

    for(int f = 0; f < N_FLOORS; f++){
        elevio_buttonLamp(f, BUTTON_HALL_DOWN, 0);
        elevio_buttonLamp(f, BUTTON_HALL_UP, 0);
        elevio_buttonLamp(f, BUTTON_CAB, 0);
    }


    if (elevio_floorSensor() != -1) {
        // Wait 3 seconds after the stop-button is released
        clock_t start_time = clock();
        double seconds_passed = 0;
        while(seconds_passed < 1.5) {
            seconds_passed = (double)(clock() - start_time) / CLOCKS_PER_SEC;

            // Sjekke for bestillinger under ventetid
            ctrl_scanButtonInputs(anElevator, orderHead, cabOrderHead);

            // Obstruksjonsfunksjonalitet
            while (elevio_obstruction()) {
                continue;
            }

            int stopValue = elevio_stopButton();
            if (elevio_stopButton()) {
                ctrl_stop(anElevator, orderHead, cabOrderHead, &stopValue);
            }
        }
    }

    // fjerne alle lys



    elevio_doorOpenLamp(0);
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
