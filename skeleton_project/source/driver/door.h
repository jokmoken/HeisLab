#pragma once
#include <time.h>
#include <stdio.h>
#include "elevio.h"
#include "fetch_signals.h"
#include "elevio.h"
#include "fsm.h"

/**
 * @file timer.h
 * @brief Hovedfilen for heisprogrammet. Inneholder logikk for initialisering og håndtering av heisens tilstander.
 */


/**
 * @brief Holder heisdøren åpen i en begrenset periode mens den samler signaler fra knappene.
 * 
 * Denne funksjonen aktiverer døråpen-lampen og holder heisdøren åpen i omtrent 3 sekunder.
 * I løpet av denne tiden sjekker den kontinuerlig etter knappetrykk for å legge til nye forespørsler
 * i forespørselskøen. Dette gjør det mulig for passasjerer å sende forespørsler mens døren er åpen.
 * Når tidsperioden er over, slukkes døråpen-lampen, og døren lukkes.
 * 
 * @param elevator En peker til heisens tilstandsstruktur, som inkluderer forespørselskøen.
 */
void holdDoorOpen(Elevator* elevator);