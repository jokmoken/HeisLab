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
#include "queue.h"

//#define N_FLOORS 4


//#define MAX_FLOOR 6
//int floorRequestqueue[] = {11, 21, 22, 31, 32, 42}
//bool floorRequestqueue[MAX_FLOOR] = {false};

/*
typedef enum {
    NO_ORDER = 0,
    BUTTON_HALL_UP = 1,
    BUTTON_HALL_DOWN = 2,
    BUTTON_CAB = 3,
} Orderlist;
*/

void addRequest(Elevator *elevator, int floor, ButtonType order){
    if(floor >= 0 && floor < N_FLOORS) {
        elevator->requestQueue[floor][order] = 1;
    }

}

void removeRequest(Elevator *elevator, int floor){
    for(int i = 0; i < N_BUTTONS; i++){
        elevator->requestQueue[floor][i] = 0;
    };
}

void emergency_clean_all(Elevator *elevator){
    for(int i = 0; i < N_FLOORS; i++){
        for(int j = 0; j < N_BUTTONS; j++){
            elevator->requestQueue[i][j] = 0;
        }
    }
}





