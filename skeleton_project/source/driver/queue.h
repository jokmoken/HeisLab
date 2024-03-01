#pragma once
#include "fsm.h"
#include "elevio.h"
#include "con_load.h"




typedef enum {
    No_order = 0,
    Call_up = BUTTON_HALL_UP,
    Call_down = BUTTON_HALL_DOWN,
    Call_inside_cab = BUTTON_CAB,
} Orderlist;

void addRequest(Elevator *elevator, int floor, Orderlist order);
void removeRequest(Elevator *elevator, int floor);
void emergency_clean_all(Elevator *elevator);