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


#define Between_floors -1
static int current_floor = 0;
void update_floor(){
    current_floor = elevio_floorSensor();
}

void Initial_state(){
    emergency_clean_all();
    Update_floor();
    if (current_floor == Between_floors){

    }
}