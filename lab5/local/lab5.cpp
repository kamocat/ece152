// g++ serial.c++ -lboost_system -lws2_32 -D _WIN32_WINNT=0x0501

#include <iostream>
#include "SimpleSerial.h"

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{
	int return_value = 0;

	string inputstr;
	cout << "Lab 5 Code Started" << endl;

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
		 * Start reading data from your wunderboard and 
		 * displaying it to the screen.
		 * Check if there is input to be read from the keyboard.
		 * If there is THEN read it, otherwise ignore the keyboard
		 * If you just read data at it is 'EXIT' retun from the 
		 * program.
		 */

		/* The constructor takes the COM port and the buad rate */
		SimpleSerial output( "/dev/ttyUSB0", 9600 );
		
		for( int i = 0; i < 150; ++i ) {
			cout<<output.readLine()<<endl;
		}



		
    } catch(boost::system::system_error& e)
    {
        cout<<"Error: "<<e.what()<<endl;
        return_value = -1;
    }

	return return_value;
}
