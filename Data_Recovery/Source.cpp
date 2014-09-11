#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;
using std::getline;
using std::vector;
using std::map;
using std::stoi;

int main(int argc, char *argv[])
{
	string input_file;

	// Check first argument if it exists for input file, otherwise ask user
	if (argc > 1)
	{
		input_file = argv[1];
	}
	else
	{
		cout << "Please enter the path to your input file: " << endl;
		cin >> input_file;
	}

	// Open input file and check if successfully opened
	ifstream ifs(input_file);
	if (!ifs)
	{
		cout << "Failed to open input file." << endl;
		return 1;
	}

	// Cycle through each line in file
	string line;
	while (getline(ifs, line))
	{
		// Break line into two strings based on semicolon
		istringstream iss(line);
		string scrambled_sentence, pattern;
		getline(iss, scrambled_sentence, ';');
		getline(iss, pattern, ';');

		// Convert pattern string into ints
		vector<int> number_pattern;
		iss.str("");
		iss.clear();
		iss.str(pattern);
		string temp;
		while (getline(iss, temp, ' '))
		{
			int number = stoi(temp);
			number_pattern.push_back(number);
		}

		// Find missing number in pattern
		int number_of_elements = number_pattern.size();
		int missing_number = (number_of_elements + 1)*(number_of_elements + 2) / 2;
		for (auto &number : number_pattern)
		{
			missing_number -= number;
		}
		number_pattern.push_back(missing_number);

		// Unscramble sentence and print to output
		iss.str("");
		iss.clear();
		iss.str(scrambled_sentence);
		map<int, string> my_sentence;
		for (auto &n : number_pattern)
		{
			string temp;
			getline(iss, temp, ' ');
			my_sentence[n] = temp;
		}
		for (auto beg = my_sentence.begin(); beg != my_sentence.end(); beg++)
		{
			cout << beg->second << " ";
		}
		cout << endl;
	}
	return 0;
}