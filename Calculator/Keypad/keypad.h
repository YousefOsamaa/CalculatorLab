/*
 * keypad.h
 * Algorithm to take rows and loop on them
 * And uses ACTIVE LOW logic to work with Keypad
 * Input from Port C (Rows) and Output from Port B (Columns) (Default)
 * Created: 26/3/2022 10:42:53 PM
 * Author : Ahmed El-Deeb
 */ 
#ifndef KEYPAD_H_
#define KEYPAD_H_

//Macros for configuration
#define INPUT_PORT_DIRECTION	DDRC
#define INPUR_PORT				PORTC
#define INPUT_PIN				PINC
#define OUTPUT_PORT_DIRECTION	DDRB
#define OUTPUT_PORT				PORTB
#define KEYPAD_DEFAULT_VALUE    0xFF

#define PRESSED      1
#define NOT_PRESSED  0


char keypad_scan();

#endif