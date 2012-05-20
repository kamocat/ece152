/*
 * This is attempt 2 for assignment 0.
 * CPP assignment 0.
 * I was having trouble with the class stuff, so I'm resorting to  what
 * I'm comfortable with so that I can get it done on time.
 * However, the functions will probably be very similar.
 *
 * The purpose of this program is to prompt the operator with two
 * multiple-choice questions, let them guess, and tell them if
 * they're right or wrong.
 *
 * Created by Marshal Horn
 */

#include <iostream>
#include <string>


using namespace std;

struct mutlti_choice{
	string question; 
	string options[4]; 
	char correct;
	string follow_up;
};

int pose( struct multi_choice question ){
	// print the question
	cout << question.question << endl;
	for( int i = 0; i < 4; ++i ) {
		cout << question.options[i] << endl;
	}

	string in;
	int return_value;

	cin>>in;
	if( in[0] == question.correct ) {
		cout << "Good Job!" << endl;
		return_value = 0;
	} else {
		cout << "Sorry, option " << in << " is not correct." << endl;
		cout << question.follow_up << endl;
		return_value = 1;
	}

	return return_value;
}


int main( int argc, char **argv ) {
	struct multi_choice q1;
	q1.question = "How many sopranos does it take to change a lightbulb?";
	q1.options = { "One", "Two", "Five", "Twenty" };
	q1.correct = 'A';
	q1.follow_up = "It only takes one.  She holds the lightblub, and the world\
					spins around her.";

	pose( q1 );

	return 0;
}

