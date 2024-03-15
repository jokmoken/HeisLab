#pragma once
#include "fsm.h"
#include "elevio.h"
#include "con_load.h"

/**
 * @file queue.h
 * @brief Funksjonalitet for køssystem
 *
 * Denne filen innehar funksjonalitet for hvordan en legger til ordre i kø,
 * hvordan en fjerner alle ordre i en etasje,
 * og hvordan en tømmer køen ved nødstopp
 */


/**
 * @brief Legger til en forespørsel i heisens forespørselskø.
 * 
 * Denne funksjonen legger til en forespørsel for en bestemt etasje og knappetype i heisens
 * forespørselskø. Hvis etasjen er gyldig, vil den tilsvarende forespørselen bli markert som aktiv.
 * 
 * @param elevator En peker til heisens tilstandsstruktur.
 * @param floor Etasjen hvor forespørselen kommer fra.
 * @param order Typen av knapp som ble trykket (f.eks. kall opp, kall ned, eller kabin).
 */
void addRequest(Elevator *elevator, int floor, ButtonType order);

/**
 * @brief Fjerner alle forespørsler for en gitt etasje fra heisens forespørselskø.
 * 
 * Denne funksjonen går gjennom alle knappetyper for en spesifikk etasje og fjerner
 * alle aktive forespørsler ved å sette dem til 0.
 * 
 * @param elevator En peker til heisens tilstandsstruktur.
 * @param floor Etasjen hvor alle forespørsler skal fjernes.
 */
void removeRequest(Elevator *elevator, int floor);

/**
 * @brief Fjerner alle forespørsler fra heisens forespørselskø som en del av nødprosedyren.
 * 
 * Denne funksjonen går gjennom hele forespørselskøen og setter hver eneste forespørsel til 0,
 * effektivt tømmende køen. Dette er ment å bli brukt i nødsituasjoner for å resette heisens tilstand.
 * 
 * @param elevator En peker til heisens tilstandsstruktur.
 */
void emergency_clean_all(Elevator *elevator);