#include "elevio.h"
#include "con_load.h"
#include "fsm.h"
#include "tests.h"
#include "assert.h"

void testMoveToFloor() {
    Elevator elevator;

    initializeElevator(&elevator);

    //manuelt satt requestqueue
    elevator.requestQueue[1][BUTTON_CAB] = 1;
    handleIdleState(&elevator);
    assert(elevator.state == Moving_Up || elevator.state == Moving_Down);
    printf("Test move to floor passed");

}