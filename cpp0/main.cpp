/*
 * The goal of this assignment is to create a question game, where someone is
 * prompted with a question, and four answers to select from.  When they select
 * an answer (by typing in A, B, C, or D), they are told whether they are
 * correct or not.
 * I would like to use this assignment as an opportunity to practice OOP, so
 * I will make a question class, which includes the question and four answers,
 * as well as a method to ask the question,
 *
 * Created by Marshal Horn.
 */
#include <iostream>
#include <string.h>

using namespace std;

class question{
	public:
		question( string query,
				string response_A,
				string response_B,
				string response_C,
				string response_D,
				char answer,
				string explanation ) {
			prompt = query;
			answers[0] = response_A;
			answers[1] = response_B;
			answers[2] = response_C;
			answers[3] = response_D;
			follow_up = explanation;

			/*
			 * Make sure answer is between A and D.
			 * These don't catch everything, but they
			 * coerce common mistakes into the valid
			 * range
			 */
			if( answer >= 'a' ) {
				answer -= 'a';
			}
			if( answer < 'A' ) {
				answer += 'A';
			}
			correct = answer;
		}


		/* This returns 0 if they got it right, and their response if they got it wrong */
		int ask( void ) {
			/* Ask the prompt */
			cout<<prompt<<endl;

			/* Ask each question */
			for( int i = 0; i < 4; ++i ) {
				cout<<(char)( i + 'A')<<". "<<answers[i]<<endl;
			}


			int return_value = -1;
			string response;

			while( return_value < 0 ) {
				cin>>response;

				if( response[0] == correct ) {
					cout<<"Good job!"<<endl;
					return_value = 0;
				} else if( response[0] > 'D' || response[0]< 'A' ) {
					cout<<"That response is out of range.  Please enter A, B, C, or D."<<endl;
				}	else {
					cout<<"Sorry, "<<response<<" is not correct."<<endl;
					cout<<follow_up<<endl;
					return_value = 1;
				}
			}
			
			/* Leave a few lines space between jokes */
			cout<<"\n\n"<<endl;

			return return_value;
		}


		~question( void ) {
			/* Nothing to clean up */
		}



	private:
		string prompt;
		string answers[4];
		char correct;
		string follow_up;
};




/************ MAIN FUNCTION *************************/


int main( int argc, char **argv ) {
	question joke1( "How many sopranos does it take to change a lightbulb?",
			"One",
			"Two",
			"Fifteen",
			"One Hundred",
			'A',
			"It only takes one.  She holds up the bulb, and the world spins around her." );

	question joke2( "If Elvis is alive, then he is living on Neptune.  That statement is:",
			"True",
			"False",
			"True AND False",
			"None of the above",
			'A',
			"The statement is vaccuously true, because the hypothesis is false.");

	joke1.ask();
	joke2.ask();
	cout<<"Thanks for playing!"<<endl;

	return 0;
}
