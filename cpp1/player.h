#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


class Player{
public:
	friend class Rps;
	
	Player(std::string name){
		srand ( time(NULL) );
		
		Player::name = name;
		won = 0;
		lost = 0;


	}

	std::string get_name() {
		return name;
	}

	int score() {
		return won;
	}

	int score( int *wins, int *losses ) {
		*wins = won;
		*losses = lost;
		return won;
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
	/* Extra Challenge 1: 
	 * Get User input for one of the guesses*/
		cout<<"What is your guess?  Rock, Paper, or Scissors?"<<endl;
		std::string guess;
		cin>>guess;
		return guess;
	}




	int win() {
		++won;
		cout<<name<<" has now won "<<won<<" times!"<<endl;
		return won;
	}

	int lose() {
		++lost;
		cout<<name<<" has now lost "<<won<<" times!"<<endl;
		return lost;
	}

/*Extra Challenge 2: 
	Add the Players name to the object and it constructor. 
	Add a function to get the name/change it*/
private:
	std::string name;
	int won;
	int lost;
	
	
};
