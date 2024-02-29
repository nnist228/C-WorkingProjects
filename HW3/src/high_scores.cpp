#if _WIN32
#define _CRT_SECURE_NO_WARNINGS // to use fopen in windows without warnings of using fopen_s instead 
#else
#endif

//include files
#include <sys/stat.h> //fstat, struct stat
#include <cctype> // isgraph 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "theGame.h"
#include <map>

//functions prototypes 
void Greetings(std::string&);
void GettingResults(std::ifstream &, std::multimap<int, std::string>&);
void GettingBestResults(std::ifstream &, std::map<std::string, int>& Results);
void printResToFile(std::string_view , int , std::ofstream&);
void printBestResToFile(const std::string&, int, const std::string&);
std::ifstream fileReadOpen(const std::string&);
std::ofstream fileWriteOpen(const std::string&);
void Info();
template<class T>
void outputResults(T&);


int main(int argc, char** argv) {

	const std::string high_scores_filename = "high_scores.txt"; // file name variable
	std::string user_name;
	int attempts;
	if(argc == 4){
		std::string argv_1{argv[1]};
		std::string argv_2{argv[2]};
		std::string argv_3{argv[3]};
		//see -max and -leave-best params below for comments
		if(argv_1 == "-leave-best" && argv_2 == "-level"){
			std::stringstream param3value{argv_3};
			unsigned parameter;
			try{
				param3value >> parameter;
				if(param3value.fail() || !param3value.eof()){
					throw std::invalid_argument("invalid value: " + argv_2);
				}
			}
			catch(std::exception& ex){
				std::cerr << "Invalid parameter value" << std::endl;
				std::cerr << "Error: " << ex.what() << std::endl;
				exit(EXIT_FAILURE);
			}
			switch(parameter){
				case 1: parameter = 10;
				break;
				case 2: parameter = 50;
				break;
				case 3: parameter = 100;
				break;
				default: parameter = MAX_VALUE;
				break;
			}
			Greetings(user_name);
			attempts = theGame(parameter);
			printBestResToFile(user_name, attempts, high_scores_filename);
		}

	} else if(argc == 3){ // go here for a two arguments call
		std::string argv_1{argv[1]};
		std::string argv_2{argv[2]};
		if(argv_1 == "-max"){ // first argument is -max
			std::stringstream param2value{argv_2};
			unsigned parameter;
			try{
				param2value >> parameter;
				if(param2value.fail() || !param2value.eof()){
					throw std::invalid_argument("invalid value: " + argv_2);
				}
			}
			catch(std::exception& ex){
				std::cerr << "Invalid parameter value" << std::endl;
				std::cerr << "Error: " << ex.what() << std::endl;
				exit(EXIT_FAILURE);
			}
			Greetings(user_name); // getting user name
			attempts = theGame(parameter);	// playing the game
			std::ofstream o_file{fileWriteOpen(high_scores_filename)};
			printResToFile(user_name, attempts, o_file);	// printing results to the file
			std::ifstream in_file{fileReadOpen(high_scores_filename)};
			std::multimap<int, std::string> Results; 
			GettingResults(in_file, Results);	// getting results from the file
			outputResults(Results);	// output those results 
		} else if(argv_1 == "-level"){
			std::stringstream param2value{argv_2};
			unsigned parameter;
			try{
				param2value >> parameter;
				if(param2value.fail() || !param2value.eof()){
					throw std::invalid_argument("invalid value: " + argv_2);
				}
			}
			catch(std::exception& ex){
				std::cerr << "Invalid parameter value" << std::endl;
				std::cerr << "Error: " << ex.what() << std::endl;
				exit(EXIT_FAILURE);
			}
			switch(parameter){
				case 1: parameter = 10;
				break;
				case 2: parameter = 50;
				break;
				case 3: parameter = 100;
				break;
				default: parameter = MAX_VALUE;
				break;
			}
			// same operation as for -max call
			Greetings(user_name); // getting user name
			attempts = theGame(parameter);	// playing the game
			std::ofstream o_file{fileWriteOpen(high_scores_filename)};
			printResToFile(user_name, attempts, o_file);	// printing results to the file
			std::ifstream in_file{fileReadOpen(high_scores_filename)};
			std::multimap<int, std::string> Results; 
			GettingResults(in_file, Results);	// getting results from the file
			outputResults(Results);	// output those results 
		}
		else if(argv_1 == "-table" && argv_2 == "-best"){ // first argument is -table, second -best 
			std::ifstream in_file{fileReadOpen(high_scores_filename)};
			std::map<std::string, int> Results;
			GettingBestResults(in_file, Results); // getting only the best
			outputResults(Results); // output those best
		}
		else{
			std::cerr << ("Invalid flag") << std::endl;
			exit(EXIT_FAILURE);
		}
	} else if(argc == 2){ // go here for a one argument call
		std::string argv_1{argv[1]};
		if(argv_1 == "-table"){ // arg is -table
			std::ifstream in_file{fileReadOpen(high_scores_filename)};
			std::multimap<int, std::string> Results;
			GettingResults(in_file, Results);
			outputResults(Results);
		} else if(argv_1 == "-leave-best"){ // arg is -leave-best, we go here if we want to print a new result to the file and clear previous results if the new one is the best
			Greetings(user_name);
			attempts = theGame();
			printBestResToFile(user_name, attempts, high_scores_filename);
		} else if(argv_1 == "--help"){
			Info();
		}
		else{
			std::cerr << ("Invalid argument list for a two argument call, type --help") << std::endl;
			exit(EXIT_FAILURE);
		}
	} else if(argc == 1){
		// same operation as for -max call but theGame call with a default argument 
		Greetings(user_name);
		attempts = theGame();
		std::ofstream o_file{fileWriteOpen(high_scores_filename)};
		printResToFile(user_name, attempts, o_file);
		std::ifstream in_file{fileReadOpen(high_scores_filename)};
		std::multimap<int, std::string> Results;
		GettingResults(in_file, Results);
		outputResults(Results);
	}
	else{
		std::cerr << ("Invalid argument number, type --help") << std::endl;
		exit(EXIT_FAILURE);
	}

	return 0;
}

void Greetings(std::string& name) // greeting function to a name of a user
{
	std::cout << "Please, enter your name: ";
	std::cin >> name;
}

void GettingResults(std::ifstream &in_file, std::multimap<int, std::string>& Results) //fucntion to get all results from the file 
{
	while (true) {
		std::string username;
		int high_score;
		in_file >> username;

		in_file >> high_score;

		in_file.ignore();

		if (in_file.fail()) {
			break;
		}
		Results.emplace(std::move(high_score), std::move(username));
	}
}

void GettingBestResults(std::ifstream &in_file, std::map<std::string, int>& Results) //function to get the best results per each name from the file, 
{
	while(true){
		std::string username;
		int high_score;
		in_file >> username;

		in_file >> high_score;

		in_file.ignore();

		if (in_file.fail()) {
			break;
		}
		if(Results.count(username)){
			if(high_score < Results.at(username)){
				Results.at(username) = high_score;
			}
		} else{
			Results.emplace(std::move(username), std::move(high_score));
		}
	}
}

void printResToFile(std::string_view name, int attempts, std::ofstream& out_file){ // function to print current results to the file, text mode file writing
	out_file << name << ' ';
	out_file << attempts;
	out_file << std::endl;
}

void printBestResToFile(const std::string& name, int attempts, const std::string& file_name) // function to modify the current file if a new result is better than the previous ones.  
{						
	// !Attention, C-style code! blood from the eyes for weak (not John Wick) people who are afraid of binary mode reading/writing
	FILE* file = std::fopen(file_name.c_str(), "rb+"); // open in read+ binary mode 
	if (file == NULL) {
		std::cout << "Failed to open file for read/write binary: " << file_name << "!" << std::endl;
		exit(EXIT_FAILURE);
	}
	struct stat buf; // struct to get info about the file
	char last_char{'\0'};
	long c_size = sizeof(char);
	fstat(fileno(file), &buf);
	if(buf.st_size > 0){
		char ch;
		std::vector<size_t> start;
		std::vector<size_t> end;
		while(std::ftell(file) != buf.st_size){
			std::string name_temp;
			std::string result;
			bool begin{false};
			size_t start_index{0};
			while(std::fread(&ch, c_size, 1, file) && (isgraph(ch) || name_temp.empty())){ // getting a name from the file
				if(isgraph(ch))
				{
					name_temp += ch;
					if(!begin){
						begin = true;
						start_index = ftell(file) - 1;
					}
				}
			}
			size_t end_index{0};
			while(std::fread(&ch, c_size, 1, file) && (isgraph(ch) || result.empty())){ // getting a result from the file
				if(isgraph(ch))
				{
					result += ch;
					end_index = ftell(file) - 1;
				}
			}
			if(name_temp == name){ // if a name == the name, compare results
				if(stoi(result) <= attempts){ // if a result from the file is better, we do nothing to the file data, add the new result afterwards.
					fclose(file);
					std::ofstream o_file{fileWriteOpen(file_name)};
					printResToFile(name, attempts, o_file);
					return;
				}
				start.push_back(start_index);
				end.push_back(end_index);
			}
			last_char = ch;
		}
		// we go futher only if the new result is better than anything else for this person in the file
		size_t i{0};
		ch = ' ';
		while(i < start.size()){
			std::fseek(file, start.at(i), SEEK_SET);
			for(size_t j{start.at(i)}; j <= end.at(i); j++){
				fwrite((char*)&ch, c_size, 1, file);
			}
			i++;
		}
	}
		fclose(file); // closing the file descriptor 
		std::ofstream o_file{fileWriteOpen(file_name)}; 
		if(last_char != '\n' && last_char != '\0'){ // checks if we need a new line before
			o_file << std::endl;
		}
		printResToFile(name, attempts, o_file); // simple text mode writing to the end of the file 
}

template<class T>
void outputResults(T& Results) // template function for Results output 
{
	std::cout << "High scores table:" << std::endl;
	for(const auto& [param1, param2]: Results){
		std::cout << param1 << " : " << param2 << std::endl;
	}
}

std::ifstream fileReadOpen(const std::string& file_name) // function to create ifstream for a future input from the file, creates if possible
{	
	std::ifstream in_file{file_name};
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << file_name << "!" << std::endl;
		exit(EXIT_FAILURE);
	}
    return in_file;
}

std::ofstream fileWriteOpen(const std::string& file_name) // function to create ifstream for a future output from the file, creates if possible
{	
	std::ofstream o_file{file_name, std::ios_base::app};
	if (!o_file.is_open()) {
		std::cout << "Failed to open file for write: " << file_name << "!" << std::endl;
		exit(EXIT_FAILURE);
	}
    return o_file;
}

void Info()
{
	std::cout << "Commands: -max unsigned_arg(any to set the greatest possible number to guess minus 1)) || -leave-best -level int_arg(1 or 2 or 3) || -leave-best || -table || -table -best\n";
	std::cout << "Level 1: for numbers between 0 and 9\n";
	std::cout << "Level 2: for numbers between 0 and 49\n";
	std::cout << "Level 3: for numbers between 0 and 99" << std::endl;
}
