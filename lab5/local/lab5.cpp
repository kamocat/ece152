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

	enum state { E, X, I, T, done };
	enum state exit_yet = E;
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
		
		do{
			/*
			 * Check if there is input to be read from the keyboard.
			 * If there is THEN read it, otherwise ignore the keyboard
			 * If you just read data at it is 'EXIT' retun from the 
			 * program.
			 */
			string user_input;
			int p;

			while( (p = kbhit()) ) {

				// Use this to see when kbhit responds
				// cout<<p;

				ch = getchar();

				// Add character to string
				user_input += ch;

				switch( exit_yet ){
					case E:
						exit_yet = (ch == 'e' ) ? X : E;
						continue;
					case X:
						exit_yet = (ch == 'x' ) ? I : E;
						continue;
					case I:
						exit_yet = (ch == 'i' ) ? T : E;
						continue;
					case T:
						exit_yet = (ch == 't' ) ? done : E;
						continue;
					default:
						break;
				}
				
			}
			cout<<user_input<<endl;
			// wunderboard.writeString( user_input );
			/*
			 * Start reading data from your wunderboard and 
			 * displaying it to the screen.
			 */
			std::cout<<wunderboard.readLine()<<std::endl;



		}while( exit_yet != done );
		
    } catch(boost::system::system_error& e)
    {
        cout<<"Error: "<<e.what()<<endl;
        return_value = -1;
    }

	return return_value;
}
