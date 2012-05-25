#include "kbhit.hpp"
#include <iostream>

using namespace std;

int main(void){
	char ch = ' ';
	enum state { E, X, I, T, done };
	enum state exit_yet = E;

	changemode(1);
	do{
		if( kbhit() ) {
			ch = getchar();
			switch( exit_yet ){
				case E:
					exit_yet = (ch == 'e' ) ? X : E;
					break;
				case X:
					exit_yet = (ch == 'x' ) ? I : E;
					break;
				case I:
					exit_yet = (ch == 'i' ) ? T : E;
					break;
				case T:
					exit_yet = (ch == 't' ) ? done : E;
					break;
				default:
					break;
			}
		}
	}while ( exit_yet != done );
			 
			   
	changemode(0);
	return 0;
}
 
