
#include "elevio.h"
#include "queue.h"
#include "button.h"


void fetch_signals_from_button_and_addqueue(Elevator* elevator){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int activebutton = elevio_callButton(f, b);

            if(activebutton == 1){
                addRequest(elevator, f, b);

            }
        }
    }

}