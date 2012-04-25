/**
@file main.c
@brief 
@version  
@mainpage External Interrupt Example
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
#ifndef RED
#define RED 0b01000000
#define GREEN 0b10000000
#endif

#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

// Include the correct header file
#include <avr/interrupt.h>

// Include the correct ISR and fill it in!
ISR( TIMER3_COMPA_vect) {
	PORTB = GREEN;
	PORTC = ~PORTC;
}


ISR( BADISR_vect ) {
	PORTC = 0;
	PORTB = RED;
	PORTC = 0b11011011;

}

uint8_t init( void ) {

	// Need to setup the DDRx registers
	DDRB = RED | GREEN;
	DDRC = 0xFF;
	PORTE = 0x07;

	// Set up the timer and interrupt... Lets use Timer 3
	TCCR3A = 0b00000000;
	TCCR3B = 0b00001101;	// CTC mode, 1/1024 prescaler
	TCCR3C = 0b00000000;
	OCR3A = 488;	// reset at 2Hz
	TIMSK1 = 0b00000010;	// enable match A interrupt

	// Any other initializing should happen
	/* Clear the array */
	PORTB = RED | GREEN;
	PORTC = 0;
	PORTB = 0;

	// Don't forget to enable interrupts sei();
	sei();


	return 0;
}


int main (void) {

	init();

	// Jump into the while(1) loop.
	while( 1 ) {
		/* if( TIFR3 & (1<<OCF3A) ) {
			PORTB = GREEN | RED;
			PORTC = ~PORTC;
			TIFR3 |= (1<<OCF3A);
		} */
	}

	return 0;

}
