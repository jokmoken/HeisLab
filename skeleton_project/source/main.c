#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include "driver/elevio.h"
#include "driver/fsm.h"
#include "driver/queue.h"
#include "driver/fetch_signals.h"

/** 
 * @file 
 * @brief Prosjekt for tilpasset datasystem til heis
*/

Elevator elevator;

int main()
{
    elevio_init();
    //initialisering før start av løkken
    initializeElevator(&elevator);
    
    
    

    
    while(1){
        if(elevio_stopButton()){
            printf("stop button was pressed");
            transition(&elevator, Emergency, Enter);
            
        }

        
      fetch_signals_from_button_and_addqueue(&elevator);

        switch(fetch_next_state(&elevator)){
            case Idle:
            handleIdleState(&elevator);
            break;
            case Moving:
            handleMovingState(&elevator);
            break;
            case DoorOpen:
            handleDoorOpenState(&elevator);
            break;
            case Emergency:
            handleEmergencyState(&elevator);
            break;


        }
    
        nanosleep(&(struct timespec){0, 20 * 1000 * 1000}, NULL);
    
    }
    return 0;


}
