/*
	Filename: ExpCalcMain.cpp

	Authors:Evren Keskin and thats about it Jason didnt do shit

	Description: This program asks the user for a mathematical expression to calculate
	First it checks if the expression entered is mathematically valid
	If it is valid, 
	Then it shows the calculation of the expression using both postfix and prefix logic
	Each calculation shows conversion into postfix and prefix format
	As well as the steps done during the calculation of the final value
	If the user input wasn't valid they are told so and asked for a new value
*/

#include "Calculator.h"
#include <iostream>
#include <string>

using namespace std;
int main()
{
	Calculator expCalc;

	
	string userInput = "";
	
	do
	{
		cout << " Welcome! This program will take a user input math expression" << endl;
		cout << "and calculate its value using postfix and prefix calculations" << endl;
		cout << "-------------------------------------------------------------" << endl;
		cout << "Enter a math expression or type exit to exit:" << endl;
		getline(cin,userInput);
		
		if (userInput != "exit")
		{
			userInput = expCalc.formatInput(userInput);
			if (expCalc.expressionValidator(userInput))
			{
				cout << "Your original expression:" << endl;
				cout << userInput << endl;
				cout << "Your expression in postfix format" << endl;
				string postfix = expCalc.postfixTransformation(userInput);
				cout << postfix << endl;
				cout << "The calculation of the postfix expression:" << endl;
				int postfixResult = expCalc.postfixCalculation(postfix);
				cout << "The final result of the postfix calculation: " << postfixResult << endl;
				cout << endl << endl;
				cout << "Your original expression again:" << endl;
				cout << userInput << endl;
				cout << "Your expression in prefix format" << endl;
				string prefix = expCalc.prefixTransformation(userInput);
				cout << prefix << endl;
				cout << "The calculation of the prefix expression:" << endl;
				int prefixResult = expCalc.prefixCalculation(prefix);
				cout << "The final result of the prefix calculation: " << prefixResult << endl;
				cout << endl << endl;
			}
			else
			{
				cout << "--------------------------------------" << endl;
				cout << "That is not a mathematical expression!" << endl;
			}
			system("pause");
			system("CLS");
		}
	} while(userInput != "exit");

	system("pause");
	return 0;
}

// example expression 5*(7-5/2+1%8-(3*3%6+4/2)/(1+1*2)) 
