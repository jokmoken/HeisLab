#include <stdio.h>
#include <time.h>
#include "timer.h"

void holdDoorOpen() {
    clock_t start_time = clock();  // Få starttiden
    double doorOpenDuration = 3 * CLOCKS_PER_SEC;  // 3 sekunder omgjort til clock ticks

    // Skru på døråpen-lampen
    elevio_doorOpenLamp(1);

    while (clock() - start_time < doorOpenDuration) {
        // løkken vil kjøre til 3 sekunder har passert
        // Tror vi kan legge inn mulighet for stopp å lese
        // av stopp knappen her selv om døren er åpen
        //Legg til add to queue? ikke mulig å legge inn nye
        //bestillinger når døra er åpen
    }

    // Skru av døråpen-lampen
    elevio_doorOpenLamp(0);
}