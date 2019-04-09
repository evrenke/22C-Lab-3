#include "Calculator.h"

void Calculator::addOperand(int operand)
{
	operands.push(operand);
}

void Calculator::addOperator(std::string operatorStr)
{
	operators.push(operatorStr);
}

bool Calculator::expressionValidator(std::string input)
{
	//every mathematical expression needs to have 
	//numbers and operators
	//and it needs to start with a valid number or parantheses
	//every expression needs a number operator number "sandwich"
	//to be valid
	//parantheses need to have valid subexpressions
	//which are validated recurcively
	
	bool isLookingForNumber = true;
	bool isTestingOperator = true;
	std::string firstElement = "";
	for (int ind = 0; ind < input.length(); ind++)
	{
		if ((input.at(ind) < 47 || input.at(ind) > 57) //not a number
			&& (input.at(ind) < 40 || input.at(ind) > 43) //not an opening or closing paranthesis, multiplier, or plus
			&& (input.at(ind) != 45) //not a minus sign
			&& (input.at(ind) != '/')//not a divisor
			&& (input.at(ind) != ' ') //not a space
			&& (input.at(ind) != '%')) // not a modulus
			
			return false;//this means that a non-mathematical expression character is being used
	}

	while (input.length() != 0)
	{
		if (input.find(' ') != -1)
		{
			firstElement = input.substr(0, input.find(' '));
			input = input.substr(input.find(' ') + 1, input.length());
		}
		else
		{
			firstElement = input;
			input = "";
		}
		
		if (firstElement.at(0) == 40)// opening paranthesis
		{
			if (!isLookingForNumber)
				return false;
			if (input.substr(0, input.length()).find(')') == -1)
				return false;
			//finding the appropriate closing paranthesis
			int closingParIndex = 0;
			int openedParantheses = 0;
			for (int ind = 0; ind < input.length(); ind++)
			{
				if (input.at(ind) == '(')
					openedParantheses++;
				if (input.at(ind) == ')')
				{
					if (openedParantheses != 0)
						openedParantheses--;
					else closingParIndex = ind;
				}
			}
			if (!expressionValidator(input.substr(0, closingParIndex - 1)))
				return false;
			input = input.substr(closingParIndex + 1, input.length());
			if (input.find(' ') != -1)
			{
				firstElement = input.substr(0, input.find(' '));
				input = input.substr(input.find(' ') + 1, input.length());
			}
			else
			{
				firstElement = input;
				input = "";
			}
			if (firstElement == "")
				return true;
		}
		if (firstElement.at(0) == 41)//closing paranthesis
		{
			//in a valid expression all closing paranthesis should be paired with an opening paranthesis
			//meaning the closing par skipped in the opening par test
			//should allow this if statement to never be used
			return false; //this paranthesis should have been skipped if this was a valid expression
		}
		
		if (isLookingForNumber && (firstElement.at(0) >= 48 && firstElement.at(0) <= 57))//a number
		{
			isLookingForNumber = false;
			isTestingOperator = false;
		}
		else if(isLookingForNumber) return false;
		if (isTestingOperator && !isLookingForNumber && (firstElement.at(0) == 43 || firstElement.at(0) == 45 || firstElement.at(0) == 42
			|| firstElement.at(0) == 47 || firstElement.at(0) == 37))//operator characters
		{
			isLookingForNumber = true;
		}
		else if (isTestingOperator) return false;
		isTestingOperator = true;
	}
	if(isLookingForNumber == false)
		return true;
	return false;
}

std::string Calculator::formatInput(std::string input)
{
	//change any user input into a single spaced format for other functions
	while (input.find(' ') != -1)
	{
		input = input.substr(0, input.find(' ') ) + input.substr(input.find(' ') + 1, input.length());
	}

	int length = input.length();
	int lastIndexOfElement = 0;
	if (length != 0)
	{
		switch (input.at(lastIndexOfElement))// the first element might be a number
		{
		case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9': //scanning for more numerals
			while (lastIndexOfElement < length && (input.at(lastIndexOfElement) >= 48 && input.at(lastIndexOfElement) <= 57))
			{
				lastIndexOfElement++;
			}
		break;
		default://case '+':case '-':case '*':case '/':case '%':case '(':case ')':case ' ':
			lastIndexOfElement = 1;
		break;
		}
		if (lastIndexOfElement < length)
		{
			input = input.substr(0, lastIndexOfElement) + " " + formatInput(input.substr(lastIndexOfElement, length));
		}
	}
	return input;
}

std::string Calculator::postfixTransformation(std::string input)
{
	std::string transformed = "";
	std::string removed = "";
	while (input.length() != 0)
	{
		if (input.find(' ') == -1)
		{
			removed = input;
			input = "";
		}
		else
		{
			removed = input.substr(0, input.find(' '));
			input = input.substr(input.find(' ') + 1, input.length());
		}
		
		bool isFirstNumber = true;
		if (removed.at(0) == '+')
		{
			
			while (!operators.isEmpty() && operators.peek() != "(")
			{
				transformed += operators.peek();
				operators.pop();
				transformed += " ";
			}
			operators.push(removed);
		}
		else if (removed.at(0) == '-')
		{
			while (!operators.isEmpty() && operators.peek() != "("
				&& operators.peek() != "+")
			{
				transformed += operators.peek();
				operators.pop();
				transformed += " ";
			}
			operators.push(removed);
		}
		else if( removed.at(0) == '/')
		{
			while (!operators.isEmpty() && (operators.peek() != "(" 
				&& operators.peek() != "-" && operators.peek() != "+") )
			{
				transformed += operators.peek();
				operators.pop();
				transformed += " ";
			}
			operators.push(removed);
		}
		else if (removed.at(0) == '%')
		{
			while (!operators.isEmpty() && (operators.peek() != "("
				&& operators.peek() != "-" && operators.peek() != "+")
				&& operators.peek() != "/")
			{
				transformed += operators.peek();
				operators.pop();
				transformed += " ";
			}
			operators.push(removed);
		}
		else if (removed.at(0) == '*')
		{
			while (!operators.isEmpty() && (operators.peek() != "("
				&& operators.peek() != "-" && operators.peek() != "+")
				&& operators.peek() != "%" && operators.peek() != "/")
			{
				transformed += operators.peek();
				operators.pop();
				transformed += " ";
			}
			operators.push(removed);
		}
		else if (removed.at(0) == '(')
		{
			operators.push(removed);
		}
		else if (removed.at(0) == ')')
		{
			while (!operators.isEmpty() && (operators.peek() != "("))
			{
				transformed += operators.peek();
				transformed += " ";
				operators.pop();
			}
			operators.pop();// pops a '('
		}
		else //its a number
		{
			transformed += removed;
			transformed += " ";
		}
	}
	while (!operators.isEmpty() && (operators.peek() != "("))
	{
		transformed += operators.peek();
		transformed += " ";
		operators.pop();
	}
	operators.pop();
	while (!operators.isEmpty())
	{
		transformed += operators.peek();
		transformed += " ";
		operators.pop();
	}
	transformed = transformed.substr(0, transformed.length() - 1);
	while (!operators.isEmpty())
	{
		operators.pop();
	}
	return transformed;
}

int Calculator::postfixCalculation(std::string input)
{
	int calculation = 0;
	int operandCount = 0;
	std::string removed = "";
	if (input.find(' ') == -1)
		return std::stoi(input);
	while (input.length() != 0)
	{
		if (input.find(' ') == -1)
		{
			removed = input;
			input = "";
		}
		else
		{
			removed = input.substr(0, input.find_first_of(' '));
			input = input.substr(input.find_first_of(' ') + 1, input.length());
		}
		if (removed.at(0) == '0' || removed.at(0) == '1' || removed.at(0) == '2' || removed.at(0) == '3'
			|| removed.at(0) == '4' || removed.at(0) == '5' || removed.at(0) == '6' || removed.at(0) == '7'
			|| removed.at(0) == '8' || removed.at(0) == '9')
		{
			operands.push(std::stoi(removed));
			operandCount++;
			
		}
		else if(operandCount >= 2)
		{
			int second = operands.peek();
			operands.pop();
			int first = operands.peek();
			operands.pop();
			operandCount -= 2;
			switch (removed.at(0))
			{
			case '+':
				calculation = first + second;
				std::cout << "The calculation: " << first << " + " << second << " = " << calculation << std::endl;
				break;
			case '-':
				calculation = first - second;
				std::cout << "The calculation: " << first << " - " << second << " = " << calculation << std::endl;
				break;
			case '*':
				calculation = first * second;
				std::cout << "The calculation: " << first << " * " << second << " = " << calculation << std::endl;
				break;
			case '/':
				calculation = first / second;
				std::cout << "The calculation: " << first << " / " << second << " = " << calculation << std::endl;
				break;
			case '%':
				calculation = first % second;
				std::cout << "The calculation: " << first << " % " << second << " = " << calculation << std::endl;
				break;
			}
			operands.push(calculation);
			operandCount++;
		}
	}
	operands.pop();
	while (!operands.isEmpty())
	{
		operands.pop();
	}
	return calculation;
}

std::string Calculator::prefixTransformation(std::string input)
{
	std::string transformed = "";
	std::string removed = "";
	while (input.length() > 0)
	{
		if (input.find(' ') == -1)
		{
			removed = input;
			input = "";
		}
		else
		{
			removed = input.substr(input.find_last_of(' ') + 1, input.length());
			input = input.substr(0, input.find_last_of(' '));
		}
		
			
		if (removed.at(0) == '(')
		{
			transformed += ")";
		}
		else if (removed.at(0) == ')')
		{
			transformed += "(";
		}
		else
		{
			transformed += removed;
		}
		transformed += " ";
	}
	//its formatted like postfix, but this leaves it backwards
	transformed = postfixTransformation( transformed.substr(0, transformed.length() - 1));

	std::string flipped = "";
	while (transformed.length() > 0)
	{
		if (transformed.find(' ') == - 1)
		{
			removed = transformed;
			transformed = "";
		}
		else
		{
			removed = transformed.substr(transformed.find_last_of(' ') + 1, transformed.length());
			transformed = transformed.substr(0, transformed.find_last_of(' '));
		}
		flipped += removed;
		flipped += " ";
	}
	flipped = flipped.substr(0, flipped.length() - 1);
	while (!operators.isEmpty())
	{
		operators.pop();
	}
	return flipped;
}

int Calculator::prefixCalculation(std::string input)
{
	int calculation = 0;
	int operandCount = 0;
	std::string removed = "";

	if (input.find(' ') == -1)
		return std::stoi(input);

	while (input.length() != 0)
	{
		if (input.find(' ') == -1)
		{
			removed = input;
			input = "";
		}
		else
		{
			removed = input.substr(input.find_last_of(' ') + 1, input.length());
			input = input.substr(0, input.find_last_of(' '));
		}
		if (removed.at(0) == '0' || removed.at(0) == '1' || removed.at(0) == '2' || removed.at(0) == '3'
			|| removed.at(0) == '4' || removed.at(0) == '5' || removed.at(0) == '6' || removed.at(0) == '7'
			|| removed.at(0) == '8' || removed.at(0) == '9')
		{
			operands.push(std::stoi(removed));
			operandCount++;
		}
		else// an operator
		{
			std::string usedOperator = removed;
			//values.push(removed);
			if (!operands.isEmpty() && operandCount >= 2)
			{
				int first = operands.peek();
				operands.pop();
				int second = operands.peek();
				operands.pop();
				operandCount -= 2;
				switch (usedOperator.at(0))
				{
				case '+':
					calculation = first + second;
					std::cout << "The calculation: " << first << " + " << second << " = " << calculation << std::endl;
					break;
				case '-':
					calculation = first - second;
					std::cout << "The calculation: " << first << " - " << second << " = " << calculation << std::endl;
					break;
				case '*':
					calculation = first * second;
					std::cout << "The calculation: " << first << " * " << second << " = " << calculation << std::endl;
					break;
				case '/':
					calculation = first / second;
					std::cout << "The calculation: " << first << " / " << second << " = " << calculation << std::endl;
					break;
				case '%':
					calculation = first % second;
					std::cout << "The calculation: " << first << " % " << second << " = " << calculation << std::endl;
					break;
				}
				operands.push(calculation);
				operandCount++;
			}
		}
	}
	calculation = operands.peek();
	operands.pop();//empties operands
	return calculation;
}