#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
 
void changemode(int dir)
{
	static struct termios oldt, newt;
	  
	/*
	 * Put CIN into raw mode so we don't have to wait for a newline,
	 * but hold onto the old configuration so we can change it back.
	 */
	if ( dir == 1 ){
	tcgetattr( STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~( ICANON | ECHO );
		tcsetattr( STDIN_FILENO, TCSANOW, &newt);
	} else{
		/* Restore the old settings */
		tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	}
}
 
int kbhit (void)
{
	struct timeval tv;
	fd_set rdfs;

	tv.tv_sec = 0;
	tv.tv_usec = 0;
			 
	FD_ZERO(&rdfs);
	FD_SET (STDIN_FILENO, &rdfs);
		 
	select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &rdfs);
					 
}

/*
 * Example Useage:
int main(void){
	int ch;
	changemode(1);
	while ( !kbhit() ){
		putchar('.');
	}
	  
	ch = getchar();
			 
	printf("\nGot %c\n", ch);
			   
	changemode(0);
	return 0;
}
 
*/
