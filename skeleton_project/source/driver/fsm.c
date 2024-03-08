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


#define Between_floors -1
static int current_Floor = 0;
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
    int last_floor = elevator->Lastfloor;
    printf("last floor is now: %d", elevator->Lastfloor);
    int last_direction = elevator->direction;

    
    // Check if there are any requests
    bool hasRequests = false;
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            
            assert(f >= 0 && f < N_FLOORS);
            assert(b >= 0 && b < N_BUTTONS);
            //sjekk om køen er tom
            if (elevator->requestQueue[f][b] > 0) {
                hasRequests = true;
                //hvis f er større gå opp
                if (f > elevator->currentFloor && f > last_floor) {
                    elevator->direction = 1;
                    transition(elevator, Moving, Enter);
                    
                }
                //når vi er mellom etasjer
                if (f > elevator->currentFloor && f < last_floor) {
                    elevator->direction = -1;
                    transition(elevator, Moving, Enter);
                   
                }
                if (f > elevator->currentFloor && f == last_floor) {
                    elevator->direction = last_direction;
                    transition(elevator, Moving, Enter);
                   
                }

                else if (f < elevator->currentFloor) {
                    elevator->direction = -1;
                    transition(elevator, Moving, Enter);
                    //break;
                //hvis ordren kommer fra samme etasje
                } else { 
                    printf("hopped to else in moving state ----------");
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
        elevator->Lastfloor = elevio_floorSensor();

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
    printf("we are hopping in and ou tof here");
    elevio_motorDirection(DIRN_STOP);
    if(elevator->currentFloor >= 0 && elevator->currentFloor < N_FLOORS){
        elevio_doorOpenLamp(1);
        


    // Tøm kø for denne etasjen: bruk funksjon?
    for (int b = 0; b < N_BUTTONS; b++) {
        elevator->requestQueue[elevator->currentFloor][b] = 0;
    }
    // Vent 3? sekunder
    //for (volatile int t = 0; t < 3; t++);
    elevio_doorOpenLamp(0); // skru av lampen
    transition(elevator, Idle, Enter);
    } else {
        printf("ERROR: current floot invalid %d", elevator->currentFloor);
        transition(elevator, Idle, Enter);
    }
}

// Ta seg av krise
void handleEmergencyState(Elevator* elevator) {
    if(elevator->state == Emergency){
            elevio_motorDirection(DIRN_STOP);
            emergency_clean_all(elevator);  // Clear all requests
            elevio_stopLamp(1);
        
        }
    
    while(elevio_stopButton()){
        
        }
    elevio_stopLamp(0);

    transition(elevator, Emergency, Exit);
    
            
        
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
                elevio_doorOpenLamp(1); 
                // Start door open timer here, then transition to Exit after timer expires
                //trenger en timer som starter her og får heisen til å transition til exit
            } else if (action == Exit) {
                elevio_doorOpenLamp(0); // Turn off door lamp
                transition(elevator, Idle, Enter); // Return to Idle after door closes
            }
            break;
        case Emergency:
            if (action == Enter) { 
                handleEmergencyState(elevator);
                
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