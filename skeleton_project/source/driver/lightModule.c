#include "lightModule.h"

void lgt_setLight(LightType lightType, int state){
    switch (lightType) {
        case LIGHT_FLOOR4_DOWN: elevio_doorOpenLamp(state); 
            break;
        default: printf("Ugyldig lys\n");
            break;
    }
}


/*
// Kode før fjernet ordrelys. Er implementert i ctrl_scanButtonInputs()
void lgt_setLight(LightType lightType, int state){
    switch (lightType) {
        case LIGHT_FLOOR4_DOWN: elevio_doorOpenLamp(state); 
            break;
        case LIGHT_FLOOR3_UP: elevio_buttonLamp();
            break;
        case LIGHT_FLOOR3_DOWN: lights->light_orderFloor3_DOWN = state; 
            break;
        case LIGHT_FLOOR2_UP: lights->light_orderFloor2_UP = state; 
            break;
        case LIGHT_FLOOR2_DOWN: lights->light_orderFloor2_DOWN = state; 
            break;
        case LIGHT_FLOOR1_UP: lights->light_orderFloor1_UP = state; 
            break;
        case LIGHT_DOOR_OPEN: lights->light_door_OPEN = state; 
            break;
        default: printf("Ugyldig lys\n");
            break;
    }
}
*/