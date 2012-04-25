/*
 * This header allows communication over serial (at least, one way)
 */
#include <stdlib.h> // for malloc
#include <string.h>	// for string manipulation functions
#include <stdio.h>	// for sprintf
#include <avr/io.h>	// for register macros

#ifndef HORNM_SERIAL_DEBUG
#define HORNM_SERIAL_DEBUG

/** This function needs to setup the variables used by the UART to enable the UART and tramsmit at 9600bps. This 
function should always return 0. Remember, by defualt the Wunderboard runs at 1mHz for its system clock.*/
unsigned char init_UART( void ) {

	/* Set baud rate to 9600 */
	UBRR1H = 0;
	UBRR1L = 12;
	/* Set the U2X1 bit to get more reliable transmission at 9600 */
	UCSR1A = 0b00000010;
	/* Enable transmitter */
	UCSR1B = 0b00001000;
	/* Set frame format: 8data, 1stop bit */
	UCSR1C = 0b00000110;

	return 0;

}

/** This function needs to write a single byte to the UART. It must check that the UART is ready for a new byte 
and return a 1 if the byte was not sent. 
@param [in] data This is the data byte to be sent.
@return The function returns a 1 or error and 0 on successful completion.*/

char send_byte(unsigned char data){
	signed char error = 1;

	if( UCSR1A & 0b00100000 ) {
		// ready to send new byte
		UDR1 = data;
		error = 0;
	}
	return error;

}

/* This function receives a single byte from UART.
 * Be careful, as the the byte can be overwritten if this isn't checked
 * often enough.
 * If no byte is received, this returns 0.
 */
char get_byte( void ) {
	char received = 0;
	if( UCSR1A & 1<<RXC1) {
		received = UDR1;
	}
	return received;
}


/** This function needs to writes a string to the UART. It must check that the UART is ready for a new byte and 
return a 1 if the string was not sent. 
@param [in] data This is a pointer to the data to be sent.
@return The function returns a 1 or error and 0 on successful completion.*/

char send_string(char *data ){
	uint8_t length = strlen( data );
	/* First check if the comm port is ready */
	char error;
	if( length > 0 ) {
		//error = send_byte( data[0] );
		//if( !error ) {
			//PORTC = data[0];
			for( char i = 0; i < length; ++i ) {
				/* Wait until send is done */
				while( !(UCSR1A & 0b00100000) );
				
				/* Now we can send the data */
				UDR1 = data[ (int)i ];
			}
		//}
	} else {
		error = 1;
	}
	return error;
}

#endif
