#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include "elevio.h"
#include "con_load.h"

#define Between_floors -1

void Update_floor(){
    int Current_floor = elevio_floorSensor();
}



void Initial_state(){
    emergency_clean_all();
    
}
