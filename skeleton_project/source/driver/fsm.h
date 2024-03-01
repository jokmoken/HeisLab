#pragma once


typedef enum {
    Idle,
    Moving_Up,
    Moving_Down,
    DoorOpen,
    Emergency
} ElevatorState;


typedef struct {
    ElevatorState state;
    int requestQueue[N_FLOORS][N_BUTTONS];
    int CurrentFloor;
}
