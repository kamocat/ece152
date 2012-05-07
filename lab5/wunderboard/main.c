/*
 * This file deploys to the wunderboard.
 * It contains a function to convert an integer to ASCII.
 * This program should count, for times a second, starting at 0
 * and going to 50, then going back down to 0, then back to 50,
 * etc.  Each time it counts it should send the new value over
 * serial.
 */

/* CONSTANTS */
#define F_CPU 1000000U
#define STRING_LENGTH 10

/* INCLUDED LIBRARIES */
// #include <uart.h>
#include <stdio.h>
#include <stdint.h>



#ifdef INTERRUPT_DRIVEN_UART
/***************************************************
 * For interrupt handling, run sei() and paste this code into your 
 * main.c file.  The surrounding "ifdef" is neccessary because it
 * is used in the header to determine whether to enable the UART
 * RCV interrupts.  (Transmit is currently not interrupt-driven).
 */
uint8_t uart_rcvd[8];	// this data is live, and unsafe
uint8_t byte_index = 255;	// start off disabled
uint8_t buffered_rcv[8];	// this data is only updated after vefiricaton

ISR( BADISR_vect ) {
	// Do nothing
}

ISR( USART1_RX_vect ) {
	byte_received = UDR1;	// copy the data before it goes away
	// Use a space to signal a new message
	if( byte_received == ' ' ) {
		// Reset the counter and clear the array
		for( byte_index = 0; byte_index < 8; ++byte_index ) {
			uart_rcvd[ (int) byte_index ] = 0;
		}
		byte_index = 0;
	} else if( byte_index < 6 ){
		// update the data
		uart_rcvd[ (int) byte_index ] = byte_received;
		byte_index = ( byte_index + 1 ) &0b00000111;

		// If this is the last byte, update the buffered data.
		if( byte_index == 6 ) {
			for( byte_index = 0; byte_index < 8; ++byte_index ) {
				buffered_rcv[ (int) byte_index ] =
					uart_rcvd[ (int) byte_index ];
			}
		}
	}


}


ISR( USART1_UDRE_vect ) {
	/* Send the next byte */
}
/*********** End interrupt-driven UART ***********/
#endif


/*
 * This function reverses a string.  It takes the string, and
 * the index of the last element of the string.
 */
uint8_t reverse_string( char *string, uint8_t end ) {
	char tmp;
	for( uint8_t i = 0; i < end; ++i ) {
		tmp = string[ (int)i ];
		string[ (int)i ] = string[ (int)end ];
		string[ (int)end ] = tmp;
		--end;
	}

	return end;
}




/*
 * This function converts an integer into an ASCII value.
 * If the value does not fit in the string provided, then the
 * most significant digits will be provided.
 * This function returns the length of the string.
 */
uint8_t int_to_ascii( int value, char *number, uint8_t length ) {
	uint8_t i = 0;
	--length;	//turn length into the max index
	for( ; value; value /= 10 ) { 

		/* Don't stomp over other values */
		if( i > length ) {
			break;
		}

		/* Copy the value over */
		number[(int) i ] = value % 10 + '0';
		++i;
	}

	number[ i ] = 0;

	reverse_string( number, (i-1) );


	return ++i;
}




int main( int argc, char **argv ) {
	char string[ STRING_LENGTH ];
	int value = 12345;
	int_to_ascii( value, string, STRING_LENGTH );

	printf("%d == %s.\n", value, string );

	return 0;
}
