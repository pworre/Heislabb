#include "door.h"


void door_open(Elevator *anElevator, Orders *orderHead, CabOrders *cabOrderHead, int *lastStop, int *stopValue){
    // DOOR_OPEN functionality
    if ((anElevator->lastFloor == anElevator->nextFloor) && (*lastStop != anElevator->lastFloor)) {
            printf("Open door...Be carefull Mr.Tomren!\n");
            *lastStop = anElevator->lastFloor;

            elevio_motorDirection(DIRN_STOP);
            anElevator->state = STATIONARY;
            elevio_doorOpenLamp(1);
            int obstruction = 0;

            // 3 sekunder ventetid
            clock_t start_time = clock();
            double seconds_passed = 0;
            while(seconds_passed < 1.5) {
                seconds_passed = (double)(clock() - start_time) / CLOCKS_PER_SEC;

                // Sjekke for bestillinger under ventetid
                ctrl_scanButtonInputs(anElevator, orderHead, cabOrderHead);

            if (orderHead->next != NULL) {
                if (anElevator->lastFloor == orderHead->next->orderFloor) {
                    que_removeCompletedOrder(&orderHead);
            }
            }
            if ((cabOrderHead->next != NULL) && (que_nextCabOrder(anElevator, cabOrderHead, orderHead) == anElevator->lastFloor)) {
                que_removeCompleteCabdOrder(anElevator, orderHead, &cabOrderHead);
            }

                // Obstruksjonsfunksjonalitet
                while (elevio_obstruction()) {
                    obstruction = 1;
                    continue;
                }

                if (obstruction == 1) {
                    // 3 sekunder ventetid
                    clock_t start_time_obstruction = clock();
                    double seconds_passed_obstruction = 0;
                    while(seconds_passed_obstruction < 1.5) {
                        seconds_passed_obstruction = (double)(clock() - start_time_obstruction) / CLOCKS_PER_SEC;
                        ctrl_scanButtonInputs(anElevator, orderHead, cabOrderHead);
                        }
                }

                *stopValue = elevio_stopButton();
                if (elevio_stopButton()) {
                    ctrl_stop(anElevator, orderHead, cabOrderHead, stopValue, lastStop);
                }
            }

            elevio_doorOpenLamp(0);
    }
}