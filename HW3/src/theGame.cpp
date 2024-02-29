#include <iostream>
#include "theGame.h"
#include <stdexcept>
#include <string>
using std::string;
#include<sstream>
using std::stringstream;
#include <ctime>

int theGame(unsigned param)
{
	std::srand(static_cast<unsigned int> (std::time(NULL))); // use current time as seed for random generator
	const int random_value = std::rand() % param;
	bool not_win = true;


	string input{""};
	int current_value;
	int attempts{0};
	do {
		try{
			std::cout << "Enter your guess: ";
			std::cin >> input;
			if (std::cin.fail()) {
				throw std::invalid_argument("Bad input");
			}
			stringstream number{input};
			number >> current_value;

			if(number.fail() || !number.eof()){
				throw std::domain_error(input);
			}
			if (current_value > random_value) {
				std::cout << "less than " << current_value << std::endl;
			}
			else if (current_value < random_value) {
				std::cout << "greater than " << current_value << std::endl;
			}
			else {
				std::cout << "you win!" << std::endl;
				not_win = false;
			}
			attempts++;
		}
		catch(std::invalid_argument& ex1){
			std::cout << ex1.what() << std::endl;
		}
		catch(std::domain_error& ex2){
			std::cout << "Bad value was entered! The value: " << ex2.what() << " Expected a number in the normal form and bounds! Try again" << std::endl;
		}
	} while(not_win);

	return attempts;
}