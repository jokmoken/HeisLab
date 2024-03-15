#pragma once
#include "fsm.h"
#include "elevio.h"
#include "con_load.h"

/**
 * @file fetch_signals.h
 * @brief Innhente signaler fra knapper som er trykket
 */


/**
 * @brief Sjekker knapper og legger til forespørsler i køen basert på aktiverte knapper.
 * 
 * Denne funksjonen går gjennom alle etasjer og knappetyper for å sjekke om en knapp er trykket.
 * Hvis en knapp er aktivert, legger funksjonen til en forespørsel i heisens kø og tenner
 * tilhørende knappelys.
 * 
 * @param elevator En peker til heisens tilstandsstruktur.
 */
void fetch_signals_from_button_and_addqueue(Elevator* elevator);