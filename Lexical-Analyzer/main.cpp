#include "lexical-analyzer.h"
#include <fstream>
#include <iostream>


int main() {
    std::ifstream inputfile;
    inputfile.open("input.txt");
    Analyzer analyze(inputfile);
	try 
	{
		analyze.run_analyzer();
	}
	catch (const std::exception&)
	{
		std::cout << "The Lexical-Analyzer ended with an error.";
	}
    return 0;
}