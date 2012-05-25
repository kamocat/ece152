#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


class Player{
public:
	friend class Rps;
	
	Player(std::string name){
		/* We don't intialize srand because we don't want it to
		 * be the same for all players. */
		// srand ( time(NULL) );
		
		Player::name = name;


	}
	
	string guess(){
		int number;
		
		number = ((int)(rand() * 10))%3;
		if (number == 0){
			return "Rock";
		}
		else if (number == 1){
			return "Paper";
		}
		else if (number == 2){
			return "Scissors";
		}
		else {
			return "Dynamite";
		}
	}
	
	string userguess(){
		
/*Extra Challenge 1: 
	Get User input for one of the guesses*/
		
	}

/*Extra Challenge 2: 
	Add the Players name to the object and it constructor. 
	Add a function to get the name/change it*/
private:
	std::string name;
	int won;
	int lost;
	
	
};
