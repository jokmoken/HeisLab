#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "elevio.h"
#include "con_load.h"
#include "fsm.h"

//#define N_FLOORS 4


//#define MAX_FLOOR 6
//int floorRequestqueue[] = {11, 21, 22, 31, 32, 42}
//bool floorRequestqueue[MAX_FLOOR] = {false};


typedef enum {
    NO_ORDER = 0,
    Call_up = BUTTON_HALL_UP,
    Call_down = BUTTON_HALL_DOWN,
    Call_inside_cab = BUTTON_CAB,
} Orderlist;


void addRequest(ElevatorState elevator, Orderlist order){
    if(floor >= 0 && floor < N_FLOORS) {
        
    }

}

void removeRequest(int floor, Orderlist order){

}



