#pragma once
#include "elevio.h"


typedef enum {
    Idle,
    Moving,
    DoorOpen,
    Emergency
} ElevatorState;

typedef enum {
    Enter,
    Do, 
    Exit,
} Action;

typedef struct {
    ElevatorState state;
    int requestQueue[N_FLOORS][N_BUTTONS];
    int currentFloor;
    int direction; // 1 is up, -1 is down, 0 is idle
} Elevator;

//void Initial_state();

void initializeElevator(Elevator* elevator);
void handleIdleState(Elevator* elevator);
void handleMovingState(Elevator* elevator);
void handleDoorOpenState(Elevator* elevator);
void handleEmergencyState(Elevator* elevator);
void transition(Elevator* elevator, ElevatorState newState, Action action);
ElevatorState fetch_next_state(Elevator* elevator);
