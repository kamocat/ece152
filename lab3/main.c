/**
 * Last modified by Marshal Horn
@file main.c
@brief Lab 2 Starter Code
@version .01 
@mainpage Lab 2 Starter Code

@section intro Code Overview
 
@section hw Hardware Pin Out
Port A:
A0 - A3 : Push Buttons
A4 - A7 : Slide Switches 

Port B:
B0 - B3 : SPI (SD Card)
B4		: Nothing
B5		: Audio Out
B6 		: Red Enable 
B7 		: Green Enable

Port C:
C0 - C7 : LED Array (Row)

Port D:
D0 - D1 : Nothing
D2		: Serial RX
D3		: Serial TX
D4 - D7	: Nothing

Port E:
E0 - E2 : LED Array (Column)
E3		: USB (UID)
E4 - E5	: Nothing
E6		: Relay
E7		: Nothing

Port F:
F0 		: ADC Channel 0
F1 		: ADC Channel 1
F2 		: ADC Channel 2
F3 		: ADC Channel 3
F4		: ADC Channel 4 (Audio In)
F5 		: ADC Channel 5 (Accel X Axis)
F6 		: ADC Channel 6 (Accel Y Axis)
F7 		: ADC Channel 7 (Accel Z Axis (if installed))

*/

/** Includes */
#include <avr/io.h>
#include <util/delay.h>

/** Constants */
#define F_CPU 1000000U


/** Global Variables */

/** Functions */

/** The initialize() function initializes all of the Data Direction Registers for the Wunderboard. Before making changes to DDRx registers, ensure that you have read the peripherals section of the Wunderboard user guide.*/
void initialize(void) {
	/** Port A is the switches and buttons. They should always be inputs. ( 0 = Input and 1 = Output )*/
	DDRA=0b00000000;

	/** Port B has the LED Array color control, SD card, and audio-out on it. Leave DDRB alone. ( 0 = Input and 1 = Output )*/
	DDRB=0b11000000;

	/** Port C is for the 'row' of the LED array. They should always be outputs. ( 0 = Input and 1 = Output )*/
	DDRC=0b11111111;

	/** Port D has the Serial on it. Leave DDRB alone. ( 0 = Input and 1 = Output )*/
	DDRD=0b00000000;

	/** Port E has the LED Array Column control out on it. Leave DDRE alone. ( 0 = Input and 1 = Output )*/
	DDRE=0b00000111;

	/** Port F has the accelerometer and audio-in on it. Leave DDRF alone. ( 0 = Input and 1 = Output )*/
	DDRF=0b00000000;
}

/** The clearArray() function turns off all LEDS on the Wunderboard array. It accepts no inputs and returns nothing*/
void clear_array(void)
{
	PORTC = 0x00;
	PORTB |= (1 << PB6) | (1 << PB7);		/** Enable latches*/
}




/************** TIMER0 SETUP ********************/


unsigned char set_timer0(unsigned char clock, unsigned char count) {
	/*
	 * This function configures how fast the timer rolls over.
	 * The clock is masked and copied to CS02:0.
	 * The count is copied to OCR0A, as the value the timer rolls over at.
	 */
	clock &= 0x07;	// mask to last three bits
	TCCR0B = clock;	// update clock
	OCR0A = count;

	/* Return an error only if clock or count are equal to zero */
	return ( !(clock) | !(count) )? 1 : 0;
}



unsigned char init_timer0( void ) {
	/* Clear timer on match - don't change outputs */
	TCCR0A = 0b00000010;

	/* Set the timer to overflow every 1/4 seconds */
	set_timer0( 5, 250 );

	return 0;	// this function never fails
}

unsigned char check_timer0( void ) {
	/* 
	 * Check the OCFA flag.  If it is set, clear it and return 1.
	 * Otherwise, return 0
	 */

	unsigned char return_value;

	if( TIFR0 & 0b00000100 ) {
		/* Clear the flag by writing one to it */
		TIFR0 |= 0b00000100;

		return_value = 1;
	} else {
		return_value = 0;
	}
	return return_value;
}







/**************** Main Function *****************/

int main (void) {
	/** Local Varibles */
	
	initialize();
	clear_array();


	init_timer0();

	while( 1 ) {
		if( check_timer0() ) {
			PORTC = ~ PORTC;
		}
	}

	return 0;
}//main
