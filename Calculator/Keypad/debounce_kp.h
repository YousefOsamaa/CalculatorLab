/*
 * debounce_kp.c
 * Algorithm to take rows and loop on them
 * And uses ACTIVE LOW logic to work with Keypad
 * Input from Port C (Default)
 * Created: 26/3/2022 10:42:53 PM
 * Author : Ahmed El-Deeb
 */ 

#ifndef DEBOUNCE_KP_H_
#define DEBOUNCE_KP_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

volatile int button;

static inline void debounce(int Row){
	
	static int count = 0;
	static int button_state = 0;
	int current_state = (~INPUT_PIN & (1<<Row)) != 0;
	
	if (current_state != button_state)
	{        
		 count++;
		 
		if (count >= 4) {
			
			button_state = current_state;
			if (current_state != 0) button = 1;
			count = 0;
		}
	}
	else count = 0;
	
}

#endif