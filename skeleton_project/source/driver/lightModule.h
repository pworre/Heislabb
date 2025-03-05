#pragma once

/*
typedef struct {
    int light_orderFloor4_DOWN;
    int light_orderFloor3_UP;
    int light_orderFloor3_DOWN;
    int light_orderFloor2_UP;
    int light_orderFloor2_DOWN;
    int light_orderFloor1_UP;
    int light_door_OPEN;
    int light_door_CLOSED;
} Lights;
*/


typedef enum {
    LIGHT_FLOOR4_DOWN,
    LIGHT_FLOOR3_UP,
    LIGHT_FLOOR3_DOWN,
    LIGHT_FLOOR2_UP,
    LIGHT_FLOOR2_DOWN,
    LIGHT_FLOOR1_UP,
    LIGHT_DOOR_OPEN,
    LIGHT_DOOR_CLOSED
} LightType;



void lgt_setLight(LightType light, int state);