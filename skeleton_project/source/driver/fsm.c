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

void initializeElevator(Elevator* elevator) {
    elevio_init();
    elevator->currentFloor = elevio_floorSensor();
    if (elevator->currentFloor != 0) { // Sjekk om vi er i første etasje
        elevio_motorDirection(DIRN_DOWN); // hvis ikke kjør nedover
        while (elevio_floorSensor() != 0); // Vent til etasje 1 er nådd
        elevio_motorDirection(DIRN_STOP); // Stop her
    }
    //initialiser så Elevator med korrekte verdier
    elevator->currentFloor = 0; //første etasje
    elevator->direction = 0; // Idle
    //Tøm køen
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            elevator->requestQueue[f][b] = 0;
        }
    }
    elevio_floorIndicator(elevator->currentFloor);
    elevator->state = Idle; // Sett state til idle
}

// State for å ta seg av "Idle"
void handleIdleState(Elevator* elevator) {
    // Check if there are any requests
    bool hasRequests = false;
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            //sjekk om køen er tom
            if (elevator->requestQueue[f][b] > 0) {
                hasRequests = true;
                //hvis f er større gå opp
                if (f > elevator->currentFloor) {
                    elevator->direction = 1;
                    transition(elevator, Moving_Up, Enter);
                //f mindre gå ned
                } else if (f < elevator->currentFloor) {
                    elevator->direction = -1;
                    transition(elevator, Moving_Down, Enter);
                //hvis ordren kommer fra samme etasje
                } else { 
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
    elevio_doorOpenLamp(1); //skru på lys
    // Tøm kø for denne etasjen: bruk funksjon?
    for (int b = 0; b < N_BUTTONS; b++) {
        elevator->requestQueue[elevator->currentFloor][b] = 0;
    }
    // Vent 3? sekunder
    for (volatile int t = 0; t < 3; t++);
    elevio_doorOpenLamp(0); // skru av lampen
    transition(elevator, Idle, Enter);
}

// Ta seg av krise
void handleEmergencyState(Elevator* elevator) {
    if(elevator->state = Emergency){
        elevio_motorDirection(DIRN_STOP);
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            elevator->requestQueue[f][b] = 0; // Clear all requests
        }
    }
    //fyll inn hva den skulle gjøre fra kravspec
    }
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
        case Moving_Up:
            if(action = Enter){
                elevio_motorDirection(DIRN_UP);
                elevator->direction = 1;
            }

        case Moving_Down:
            if (action == Enter) {
                elevio_motorDirection(DIRN_DOWN);
                elevator->direction = -1;
            }
            break;
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
                //stopp med en gang og skru på lys for stopp
                elevio_motorDirection(DIRN_STOP); 
                elevio_stopLamp(1); 
                //Tøm køen
                for (int f = 0; f < N_FLOORS; f++) {
                    for (int b = 0; b < N_BUTTONS; b++) {
                        elevator->requestQueue[f][b] = 0;
                    }
                }
            } else if (action == Exit) {
                elevio_stopLamp(0); // Turn off stop lamp
                initializeElevator(elevator); // Reinitialize to reset the system
            }
            break;
    }
}