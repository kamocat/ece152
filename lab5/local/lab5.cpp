// g++ serial.c++ -lboost_system -lws2_32 -D _WIN32_WINNT=0x0501

#include <iostream>
#include "SimpleSerial.h"
#include "kbhit.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	int return_value = 0;

	std::string inputstr;
	std::cout << "Lab 5 Code Started" << std::endl;


	/* Turn stdin to raw mode */
	changemode(1);

	enum state { E, X, I, T, done } exit_yet;
	char ch;

	/*
	 * When you are dealing with IO devices, it is very important 
	 * that calls to them be wrapped in 'try-catch' blocks.
	 * These blocks of code tell the program 'if something goes 
	 * wrong (an exception) run whatever is in catch rather than 
	 * simply killing the program.'
	 */
    try { 
		/*
		 * Make a SimpleSerial object with the parameter for your 
		 * Wunderboard/OS.
		 * The constructor takes the COM port and the buad rate
		 */
		SimpleSerial wunderboard( "/dev/ttyUSB0", 9600 );
		std::string typed;
		
		do{
			/*
			 * Start reading data from your wunderboard and 
			 * displaying it to the screen.
			 */
			std::cout<<wunderboard.readLine()<<std::endl;


			/*
			 * Check if there is input to be read from the keyboard.
			 * If there is THEN read it, otherwise ignore the keyboard
			 * If you just read data at it is 'EXIT' retun from the 
			 * program.
			 */
			string user_input;

			while( kbhit() ) {

				ch = getchar();

				switch( exit_yet ){
					case E:
						exit_yet = ( ch == 'E' ) ? X : E;
						break;
					case X:
						exit_yet = (ch == 'X' ) ? I : E;
						break;
					case I:
						exit_yet = (ch == 'I' ) ? T : E;
						break;
					case T:
						exit_yet = (ch == 'T' ) ? done : T;
						break;
					default:
						break;
				}
				
				// Add character to string
				user_input += ch;
			}
			cout<<user_input<<endl;
			wunderboard.writeString( user_input );

		}while( exit_yet != done );
		
    } catch(boost::system::system_error& e)
    {
        cout<<"Error: "<<e.what()<<endl;
        return_value = -1;
    }

	return return_value;
}
