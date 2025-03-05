#include "lightModule.h"

void setLight(Lights *lights, LightType lightType, int state){
    switch (lightType) {
        case LIGHT_FLOOR4_DOWN: lights->light_orderFloor4_DOWN = state; 
            break;
        case LIGHT_FLOOR3_UP: lights->light_orderFloor3_UP = state;
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
    }
}