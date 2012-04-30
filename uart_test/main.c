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
#include <avr/interrupt.h>

#define F_CPU 1000000U
#include <util/delay.h>

/* Found in ../lib/ */
#include <uart.h>
#include <adc.h>
#include <led.h>

/** Constants */


/** Global Variables */
uint8_t picture[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
uint8_t i = 255;	// start off disabled
uint8_t row = 0;
uint8_t byte_received;

/** Functions */



void initialize(void) {
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


	/* Enable interrupts */
	sei();
}

ISR( BADISR_vect ) {
	// Do nothing
}

ISR( USART1_RX_vect ) {
	picture[7] = 0;
	byte_received = UDR1;
	if( byte_received == ' ' ) {
		// Reset the counter and clear the array
		for( i = 0; i < 8; ++i ) {
			picture[ (int) i ] = 0;
		}
		i = 0;
	} else if( i >= 6 ) {
		// do nothing
	} else{
		// update the data
		picture[ (int) i ] = byte_received;
		i = ( i + 1 ) &0b00000111;
		send_byte( byte_received ); // send back to terminal
	}


}



/**************** Main Function *****************/

int main (void) {
	/** Local Varibles */
	
	initialize();
	init_UART();


	while( 1 ) {




		/* Refresh display  */
		PORTB = GREEN;
		for( row = 0; row < 8; ++row ) {
			PORTC = 0;
			PORTE = row;
			PORTC = picture[ (int)row ];
			_delay_us( 100 );
		}
		PORTC = 0;
		

	}

	return 0;
}//main
