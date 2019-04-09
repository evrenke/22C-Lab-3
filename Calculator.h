#pragma once
#include <string>
#include <iostream>
#include "Stack.h"
#include "Queue.h"

class Calculator
{
protected:
	Stack<std::string> operators;
	Stack<int> operands;

	
public:
	~Calculator()
	{
		operators.~Stack();
		operands.~Stack();
	}
	void addOperand(int operand);
	void addOperator(std::string operatorInt);

	bool expressionValidator(std::string input);
	std::string formatInput(std::string input);

	std::string postfixTransformation(std::string s);
	std::string prefixTransformation(std::string s);

	int postfixCalculation(std::string s);
	int prefixCalculation(std::string s);
};