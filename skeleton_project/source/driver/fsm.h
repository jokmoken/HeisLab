#pragma once
#include "elevio.h"
#include <time.h>

/**
 * @file fsm.h
 * @brief Hovedfilen for heisprogrammet. Inneholder logikk for initialisering og håndtering av heisens tilstander.
 */

/**
 * @enum ElevatorState
 * @brief Represents the possible states of an elevator.
 *
 * The elevator can be in one of several states indicating its current operation, such as idle, moving,
 * door open, or in an emergency state.
 */
typedef enum {
    Idle,
    Moving,
    DoorOpen,
    Emergency
} ElevatorState;

/**
 * @enum Action
 * @brief Represents actions that can be performed during state transitions.
 *
 * Actions define what the elevator should do when entering, performing in, or exiting a state.
 */
typedef enum {
    Enter,
    Exit,
} Action;

/**
 * @struct Elevator
 * @brief Represents an elevator, including its state and operational parameters.
 *
 * This struct holds information about the elevator's current state, the request queue for each floor
 * and button, the current and last floor, as well as the current and last direction of movement.
 */
typedef struct {
    ElevatorState state;
    int requestQueue[N_FLOORS][N_BUTTONS];
    int currentFloor;
    int direction; // 1 is up, -1 is down, 0 is idle
    int Lastfloor;
    int LastDirection;
} Elevator;


/**
 * @brief Initialiserer heisen ved å kjøre til nærmeste etasje, tømme køen og skru av alle lys.
 * 
 * Kjører heisen nedover til en etasje detekteres. Initialiserer deretter heisens tilstand til IDLE,
 * tømmer alle forespørselskøer og skrur av alle lys.
 * 
 * @param elevator En peker til heisens tilstandsstruktur.
 */
void initializeElevator(Elevator* elevator);

/**
 * @brief Håndterer IDLE-tilstanden til heisen.
 * 
 * Sjekker forespørselskøen for oppgaver. Dersom det finnes forespørsler, bestemmer funksjonen
 * retningen heisen skal bevege seg og transisjonerer til MOVING-tilstand. Dersom ingen forespørsler
 * finnes, forblir heisen i IDLE-tilstand.
 * 
 * @param elevator En peker til heisens tilstandsstruktur.
 */
void handleIdleState(Elevator* elevator);

/**
 * @brief Sjekker om det finnes forespørsler i en gitt retning.
 * 
 * Går gjennom forespørselskøen for å finne om det er noen forespørsler i den angitte retningen
 * relativt til heisens nåværende etasje.
 * 
 * @param elevator En peker til heisens tilstandsstruktur.
 * @param direction Retningen å sjekke forespørsler i. Kan være DIRN_UP eller DIRN_DOWN.
 * @return true hvis det finnes forespørsler i den angitte retningen, ellers false.
 */
bool hasRequestsInDirection(Elevator* elevator, int direction);

/**
 * @brief Håndterer MOVING-tilstanden til heisen.
 * 
 * Fortsetter å bevege heisen i den forrige bestemte retningen. Sjekker for forespørsler på nåværende
 * etasje, og om det er nødvendig å endre tilstand basert på forespørsler og heisens posisjon.
 * 
 * @param elevator En peker til heisens tilstandsstruktur.
 */
void handleMovingState(Elevator* elevator);

/**
 * @brief Håndterer DOOR OPEN-tilstanden til heisen.
 * 
 * Åpner heisdøren, tømmer forespørselskøen for nåværende etasje, og holder døren åpen et bestemt
 * antall sekunder eller til en obstruksjon detekteres.
 * 
 * @param elevator En peker til heisens tilstandsstruktur.
 */
void handleDoorOpenState(Elevator* elevator);

/**
 * @brief Håndterer EMERGENCY-tilstanden til heisen.
 * 
 * Stopper heisen umiddelbart, tømmer alle forespørselskøer, og håndterer nødstilfellet
 * basert på heisens nåværende posisjon og tilstand.
 * 
 * @param elevator En peker til heisens tilstandsstruktur.
 */
void handleEmergencyState(Elevator* elevator);

/**
 * @brief Utfører en tilstandsendring for heisen basert på gitt ny tilstand og handling.
 * 
 * Denne funksjonen oppdaterer heisens tilstand og utfører nødvendige handlinger ved overgangen til en ny tilstand.
 * Handlingene varierer avhengig av tilstanden som blir angitt og kan inkludere å stoppe motoren, håndtere døråpninger,
 * og å reagere på nødsituasjoner.
 * 
 * @param elevator En peker til heisens tilstandsstruktur.
 * @param newState Den nye tilstanden heisen skal overgå til.
 * @param action Den handlingen som skal utføres, som kan være å entre, utføre eller forlate en tilstand.
 */
void transition(Elevator* elevator, ElevatorState newState, Action action);

/**
 * @brief Henter den neste tilstanden for heisen.
 * 
 * Denne funksjonen returnerer heisens nåværende tilstand. Det er en hjelpefunksjon som kan brukes til å spørre
 * om heisens nåværende tilstand uten å direkte få tilgang til heisens tilstandsvariabel.
 * 
 * @param elevator En peker til heisens tilstandsstruktur.
 * @return Heisens nåværende tilstand som en verdi av typen @c ElevatorState.
 */
ElevatorState fetch_next_state(Elevator* elevator);
