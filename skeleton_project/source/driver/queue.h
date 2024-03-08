#pragma once
#include "fsm.h"
#include "elevio.h"
#include "con_load.h"

/*
typedef enum {
    No_order = 0,
    Call_up = BUTTON_HALL_UP,
    Call_down = BUTTON_HALL_DOWN,
    Call_inside_cab = BUTTON_CAB,
} Orderlist;
*/

/*
typedef enum {
    NO_ORDER = 0,
    BUTTON_HALL_UP = 1,
    BUTTON_HALL_DOWN = 2,
    BUTTON_CAB = 3,
} Orderlist;
*/
void addRequest(Elevator *elevator, int floor, ButtonType order);
void removeRequest(Elevator *elevator, int floor);
void emergency_clean_all(Elevator *elevator);