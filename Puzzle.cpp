#include "Puzzle.h"
#include <fstream>

Puzzle::Puzzle(std::string fileName) 
{
	this->correctAnswer = 0;

	std::ifstream inFile(".\1.txt");
	
	int nrOfAns = 0;
	std::string answer = "";
	int correctAns = 0;

	if (inFile.is_open())
	{
		std::getline(inFile, this->question);
		inFile >> nrOfAns;
		inFile.ignore();

		for (size_t i = 0; i < nrOfAns; i++) {
			std::getline(inFile, answer);
			this->answers.push_back(answer);
		}

		inFile >> correctAns;
		this->correctAnswer = correctAns;
		inFile.ignore();
		
	}
	else
		throw("Could not open puzzle!");

	inFile.close();
}

Puzzle::~Puzzle() {}

std::string Puzzle::getAsString() 
{
	std::string answer = "";

	for (size_t i = 0; i < this->answers.size(); i++)
	{
		answer += std::to_string(i) + ": " + this->answers[i] + "\n";
	}

	return this->question + "\n" + "\n"
		+ answer + "\n";
}