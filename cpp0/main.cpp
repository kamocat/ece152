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

class question
{
	public:
		question( std::string query,
				std::string resonse_A,
				std::string resonse_B,
				std::string resonse_C,
				std::string resonse_D,
				char answer ) {
			strcpy( promt, query );
			strcpy( answers[0], response_A );
			strcpy( answers[1], response_B );
			strcpy( answers[2], response_C );
			strcpy( answers[3], response_D );

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


			int return_value;
			std::string response;

			cin>>response;
			if( response.cstring()[0] == correct ) {
				cout<<"Good job!"<<endl;
				return_value = 0;
			} else {
				cout<<"Nope, wrong answer"<<endl;
				return_value = response.cstring()[0];
			}

			return return_value;
		}


		~question( void ) {
			/* Nothing to clean up */
		}



	private:
		std::string prompt;
		std::string answers[4];
		char correct;
};



int main( int argc, char **argv ) {
	question prob1( "How many sopranos does it take to change a lightbulb?",
			"One",
			"Two",
			"Fifteen",
			"One Hundred",
			A );

	prob1.ask();

	return 0;
}
