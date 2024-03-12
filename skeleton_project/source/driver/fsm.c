#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#include "elevio.h"
#include "con_load.h"
#include "fsm.h"
#include "timer.h"
#include "queue.h"


#define Between_floors -1
bool hasRequest = false;



void initializeElevator(Elevator* elevator) {
    while(elevio_floorSensor() == Between_floors){
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);
    printf("Initialization done \n");
    
    

    transition(elevator, Idle, Enter);
    printf("state er nå: %u \n", elevator->state);
    
    
    //Tøm køen
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            elevator->requestQueue[f][b] = 0;
        }
    }
    
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            printf("%d", elevator->requestQueue[f][b]);
        }
        printf("\n");
    }
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            elevio_buttonLamp(f, b, 0);
        }
        
    }
    elevator-> Lastfloor = elevio_floorSensor();
    elevio_stopLamp(0);
    elevio_doorOpenLamp(0);
    
}

// State for å ta seg av "Idle"
void handleIdleState(Elevator* elevator) {
    elevator->currentFloor = elevio_floorSensor();
    int last_direction = elevator->direction;

    
    // Check if there are any requests
    bool hasRequests = false;
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            //sjekk om køen er tom
            if (elevator->requestQueue[f][b] > 0) {
                hasRequests = true;
                //hvis f er større gå opp
                if (f > elevator->currentFloor && f > elevator->Lastfloor) {
                    elevator->direction = 1;
                    transition(elevator, Moving, Enter);
                    
                }
                //når vi er mellom etasjer
                if (f > elevator->currentFloor && f < elevator->Lastfloor) {
                    elevator->direction = -1;
                    transition(elevator, Moving, Enter);
                   
                }
                if (f > elevator->currentFloor && f == elevator->Lastfloor) {
                    elevator->direction = (-1)*last_direction;
                    transition(elevator, Moving, Enter);
                   
                }

                if (f < elevator->currentFloor) {
                    elevator->direction = -1;
                    transition(elevator, Moving, Enter);
                    //break;
                //hvis ordren kommer fra samme etasje
                } else if (f == elevator->currentFloor) { 
                    transition(elevator, DoorOpen, Enter);
                }
                break;
            }
        }
        if (hasRequests) break;
    }
}

// Tar seg av "moving"
void handleMovingState(Elevator* elevator) {
    
    if (elevator->direction == 1) {
        elevio_motorDirection(DIRN_UP);
    } else if (elevator->direction == -1) {
        elevio_motorDirection(DIRN_DOWN);
    }

    int sensorSignal = elevio_floorSensor();
    if (sensorSignal != -1) {
        elevator->currentFloor = sensorSignal;
        elevio_floorIndicator(sensorSignal);
        elevator->Lastfloor = sensorSignal;

        // sjekk om en av etasjene har en request
        if (elevator->requestQueue[sensorSignal][0] ||
            elevator->requestQueue[sensorSignal][1] ||
            elevator->requestQueue[sensorSignal][2]) {
            transition(elevator, DoorOpen, Enter);
        }
    }
}

// Dør er åpen
void handleDoorOpenState(Elevator* elevator) {

    elevio_motorDirection(DIRN_STOP);
    // Tøm kø for denne etasjen: bruk funksjon?
    for (int b = 0; b < N_BUTTONS; b++) {
        elevator->requestQueue[elevator->currentFloor][b] = 0;
        elevio_buttonLamp(elevator->currentFloor,b,0);
    }
    //skrur på lys i 3 sekund og "låser" systemet
    holdDoorOpen();
    
    transition(elevator, Idle, Enter);
}

// Ta seg av krise
void handleEmergencyState(Elevator* elevator) {
    emergency_clean_all(elevator);
    //while(elevio_stopButton()){
        //printf("we are in an emergency state");
        if(elevator->state == Emergency){
            elevio_motorDirection(DIRN_STOP);
            emergency_clean_all(elevator);  // Clear all requests
        for (int f = 0; f < N_FLOORS; f++) {
            for (int b = 0; b < N_BUTTONS; b++) {
                //printf("queue after emergency %d", elevator->requestQueue[f][b]);
                printf("state is now: %c", elevator->state);
                elevio_buttonLamp(f,b,0);
                }
            
            }
        }
    //}

    printf("broke out of loop");
    transition(elevator, Emergency, Exit);
    printf("broke out of loop");
            
        
    }

void transition(Elevator* elevator, ElevatorState newState, Action action) {
    //oppdater state

    elevator->state = newState;
    //switch for alle de ulike statesene 
    switch (newState) {
        case Idle:
            if (action == Enter) {
                elevio_motorDirection(DIRN_STOP);
                handleIdleState(elevator); // gå inn i Idle state og sjekk om det er requests
            }
            break;
        //caser for opp og ned
        case Moving:
            if(action == Enter){
                handleMovingState(elevator);
            }
        
        case DoorOpen:
            if (action == Enter) {
                //skru på lys
                //elevio_doorOpenLamp(1); 
                // Start door open timer here, then transition to Exit after timer expires
                //trenger en timer som starter her og får heisen til å transition til exit
            } else if (action == Exit) {
                elevio_doorOpenLamp(0); // Turn off door lamp
                transition(elevator, Idle, Enter); // Return to Idle after door closes
            }
            break;
        case Emergency:
            if (action == Enter) {
                //stopp med en gang og skru på lys for stopp
                printf("inside transition");
                //elevio_motorDirection(DIRN_STOP); 
                
                elevio_stopLamp(1); 
                //handleEmergencyState(elevator);
                
            } else if (action == Exit) {
                elevio_stopLamp(0); // Turn off stop lamp
                transition(elevator, Idle, Enter); // Reinitialize to reset the system
                printf("exited emergency");
            }
            break;
    }
}

ElevatorState fetch_next_state(Elevator* elevator){
    return elevator->state;
}