#pragma once
#include "elevio.h"
#include "con_load.h"




typedef enum {
    No_order = 0,
    Call_up = BUTTON_HALL_UP,
    Call_down = BUTTON_HALL_DOWN,
    Call_inside_cab = BUTTON_CAB,
} Orderlist;
