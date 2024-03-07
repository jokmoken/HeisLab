#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include "driver/elevio.h"
#include "driver/fsm.h"
#include "driver/queue.h"

void testMoveToFloor()
{
    Elevator elevator;

    initializeElevator(&elevator);

    // manuelt satt requestqueue
    elevator.requestQueue[1][BUTTON_CAB] = 1;
    handleIdleState(&elevator);
    assert(elevator.state == Moving_Up || elevator.state == Moving_Down);
    printf("Test move to floor passed");
}

Elevator elevator;

int main()
{
    elevio_init();

    initializeElevator(&elevator);
    //initialization of elevator done before the while loop starts every time
    
    

    
    

    
    //testMoveToFloor();
    
    nanosleep(&(struct timespec){0, 20 * 1000 * 1000}, NULL);
    
    // trenger noe som sjekker hvilke knapper som er trykket på
    // eller som hele tiden henter siste knapp som er trykket på
    // en buttons fil med funksjonalitet
    /*
        while(1) {


            if(elevio_stopButton()){
                handleEmergencyState(&elevator);
            }
        }


        elevio_init();

        printf("=== Example Program ===\n");
        printf("Press the stop button on the elevator panel to exit\n");

        elevio_motorDirection(DIRN_UP);

        while(1){
            int floor = elevio_floorSensor();
            printf("Vi leser nå etasje: ");
            //printf(floor);

            if(floor == 0){
                elevio_motorDirection(DIRN_UP);
            }

            if(floor == N_FLOORS-1){
                elevio_motorDirection(DIRN_DOWN);
            }

            if(floor == 2){
                elevio_doorOpenLamp(1);
            }

            if(elevio_callButton(1,2)){
                elevio_motorDirection(0);
            }

            for(int f = 0; f < N_FLOORS; f++){
                for(int b = 0; b < N_BUTTONS; b++){
                    int btnPressed = elevio_callButton(f, b);
                    elevio_buttonLamp(f, b, btnPressed);
                }
            }

            if(elevio_obstruction()){
                elevio_stopLamp(1);
                elevio_doorOpenLamp(1);
            } else {
                elevio_stopLamp(0);
            }

            if(elevio_stopButton()){
                elevio_motorDirection(DIRN_STOP);

            }

            nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
        }

        return 0;
    } */
    
}
