#include <stdio.h>
#include <time.h>
#include "door.h"
#include "fetch_signals.h"
#include "elevio.h"
#include "fsm.h"

void holdDoorOpen(Elevator* elevator) {
    clock_t start_time = clock();  // Få starttiden
    double doorOpenDuration = (3 * CLOCKS_PER_SEC)/2;  // 3 sekunder omgjort til clock ticks

    // Skru på døråpen-lampen
    elevio_doorOpenLamp(1);

    while (clock() - start_time < doorOpenDuration) {
        
        fetch_signals_from_button_and_addqueue(elevator);
    }

    // Skru av døråpen-lampen
    elevio_doorOpenLamp(0);
}