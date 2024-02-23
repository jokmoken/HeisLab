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


void addRequest(ElevatorSystem *elevator, int floor, Orderlist order){
    if(floor >= 0 && floor < N_FLOORS) {
        elevator->requestQueue[floor][order];
    }

}

void removeRequest(ElevatorSystem *elevator, int floor){
    for(int i = 0; i < N_BUTTONS; i++){
        elevator->requestQueue[floor][i] = 0;
    };
}



void emergency_clean_all(ElevatorSystem *elevator){
    for(int i = 0; i < N_FLOORS; i++){
        for(int j = 0; j < N_BUTTONS; j++){
            elevator->requestQueue[i][j] = 0;
        }
    }
}





