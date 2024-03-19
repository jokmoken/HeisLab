#pragma once

/**
 * @file elevio.h
 * @brief Interface for elevator I/O operations.
 *
 * This file provides functions to interact with the elevator hardware,
 * such as moving the elevator, turning on/off buttons and floor lamps, and
 * detecting elevator and button states.
 */
    
#define N_FLOORS 4 /**< Antall etasjer i bygningen. */

/**
 * @enum MotorDirection
 * @brief Retninger som heismotoren kan bevege seg i.
 */
typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3 /**< Antall knapper tilgjengelig i heisen. */

/**
 * @enum ButtonType
 * @brief Typer av knapper i heisen.
 */
typedef enum { 
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2
} ButtonType;

/**
 * @brief Initialiserer heissystemets I/O-moduler.
 * 
 * Denne funksjonen initialiserer hardware for heisen og gjør den klar til bruk.
 */
void elevio_init(void);


/**
 * @brief Setter retningen til heismotoren.
 * 
 * @param dirn Den ønskede retningen for motoren.
 */
void elevio_motorDirection(MotorDirection dirn);

/**
 * @brief Styrer lysene for knappene i heisen.
 * 
 * @param floor Etasjen knappen befinner seg på.
 * @param button Typen knapp.
 * @param value Om lyset skal være på (1) eller av (0).
 */
void elevio_buttonLamp(int floor, ButtonType button, int value);

/**
 * @brief Indikerer gjeldende etasje med et lyssignal.
 * 
 * @param floor Etasjen som skal indikeres.
 */
void elevio_floorIndicator(int floor);

/**
 * @brief Styrer lyset som indikerer at døren er åpen.
 * 
 * @param value Om lyset skal være på (1) eller av (0).
 */
void elevio_doorOpenLamp(int value);

/**
 * @brief Styrer nødstopp-lyset.
 * 
 * @param value Om lyset skal være på (1) eller av (0).
 */
void elevio_stopLamp(int value);

/**
 * @brief Sjekker status for en kallknapp.
 * 
 * @param floor Etasjen hvor knappen befinner seg.
 * @param button Typen knapp som sjekkes.
 * @return Status for knappen; 1 hvis aktivert, 0 ellers.
 */
int elevio_callButton(int floor, ButtonType button);

/**
 * @brief Sjekker hvilken etasje heisen befinner seg i.
 * 
 * @return Etasjen heisen er i, eller -1 hvis den er mellom etasjer.
 */
int elevio_floorSensor(void);

/**
 * @brief Sjekker om nødstoppknappen er aktivert.
 * 
 * @return Status for nødstoppknappen; 1 hvis aktivert, 0 ellers.
 */
int elevio_stopButton(void);

/**
 * @brief Sjekker om det er en obstruksjon i døren.
 * 
 * @return Status for obstruksjon; 1 hvis det er obstruksjon, 0 ellers.
 */
int elevio_obstruction(void);
