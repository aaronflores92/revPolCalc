/*********
	Aaron Flores
	1105995
	
	revPolishCalc.cpp
	For this assignment, you are to write a program, which will calculate the results of Reverse Polish expressions that are provided by the user.

You must use a linked list to maintain the stack for this program (array implementations of the stack will not receive full credit).

You must handle the following situations (errors):
Too many operators (+ - / *)
Too many operands (doubles)
Division by zero

The program will take in a Polish expression that separates the operators and operands by a single space, and terminates the expression with an equals sign.

The program will continue to take and evaluate expressions until the user enters a zero (0) on a line by itself followed by a new line.

Your sample output should show the handling of all the error conditions as well as make use of all of the operators.
*********/
#include <iostream>
#include <string>
#include <sstream>
#include <list>

using namespace std;

bool is_numeric(const std::string& a)
{
	try
	{
		std::stoi(a);
	}
	catch(...)
	{
		return false;
	}
	return true;
	
}

int op(int& a, int& b, const std::string& op)
{
	if(op == "+") return a + b;
	if(op == "-") return a - b;
	if(op == "*") return a * b;
	if(op == "/") return a / b;
}

int main()
{
	//receive input
	std::list<int> operands;
	std::string userIn = "";
	std::string word = "";
	
	std::cout << "Please enter an expression to be evaluated. Enter a '=' to signify the end of the input or a 0 to end the program: " << endl;
	
	while(std::getline(std::cin, userIn))
	{
		//string stream to separate the input using whitespace as the delimiter
		if(userIn == "0") break;
		
		istringstream splitStr(userIn);
		std::cout << "dropping into istringstream..." << endl;
		
		while(splitStr && !splitStr.eof())
		{
			std::cout << "val now in istringstream..." << endl;
			splitStr >> word;
			
			//test if value is numeric. if so, push it onto stack (linked list)
			if(is_numeric(word)) operands.push_back(std::stoi(word));
			
			//if not numeric, check what operation to accomplish. pop values, perform operation, push result onto stack
			else if(word == "+" || word == "-" || word == "*" || word == "/")
			{
				if (operands.size() == 0) break;
				else if(operands.size() == 1)
				{
					std::cout << "Not enough operands. Your total is " << operands.back() << endl;
					//operands.pop_back();
					//break;
				}
				
				else
				{
					int a = operands.back();
					operands.pop_back();
					int b = operands.back();
					operands.pop_back();
					operands.push_back(op(b, a, word));
				}
			}
			//once finished, return expression result
			else if(word == "=")
			{
				std::cout << operands.back() << endl;
				operands.pop_back();
				std::cout << "breaking loop..." << endl;
				break;
			}
			else
			{
				std::cout << "One of the inputted values was not a number. exiting app." << endl;
				break;
			}
		}
		//once finished, return total
	}
	return 0;

}
