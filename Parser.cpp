#include "Parser.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

bool Parser::checkLowercaseLetters(string str)
{
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (str[i] < 'a' || str[i] > 'z')
		{
			return false;
		}
	}
	return true;
}

bool Parser::checkUppercaseLetters(string str)
{
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (str[i] < 'A' || str[i] > 'Z')
		{
			return false;
		}
	}
	return true;
}

bool Parser::isVectorCorrect(vector<string> v)
{
	if (!countOperators(v))
	{
		throw "Invalid line!";
		return false;
	}
	int i = 0;
	if (checkLowercaseLetters(v[i]))
	{
		if (v[i].compare("read") == 0)
		{
			if (!checkLowercaseLetters(v[i + 1]) || v.size() != 2)
			{
				throw "Invalid line!";
				return false;
			}
		}
		if (v[i].compare("print") == 0)
		{
			if (checkUppercaseLetters(v[i + 1]) && v.size() == 2)
			{
				throw "Invalid line!";
				return false;
			}
		}
	}
	i = 0;
	if (checkUppercaseLetters(v[i]))
	{
		if (!(v[i + 1].compare("[") == 0))
		{
			throw "Invalid name of function!";
			return false;
		}
		else if (!checkLowercaseLetters(v[i + 2]))
		{
			throw "Invalid argument of function!";
			return false;
		}
		else if (!(v[i + 3].compare("]") == 0))
		{
			throw "Invalid argument!";
			return false;
		}
		else if (!(v[i + 4].compare("=") == 0))
		{
			throw "Missing equality operator!";
			return false;
		}
	}
	return true;
}

bool Parser::checkNumbers(string str)
{
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			return true;
		}
	}
	return false;
}

bool Parser::isValidExpression(string str)
{
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (isOperation(str[i]) && isOperation(str[i + 1]))
		{
			throw "Two operations side by side!";
			return false;
		}
		if (checkOneTypeBrackets(str[i], str[i + 1]))
		{
			throw "No expression between brackets!";
			return false;
		}
		if ((isOpeningBracket(str[i]) && isOperation(str[i + 1])) || (isOperation(str[i]) && isClosingBracket(str[i + 1])))
		{
			throw "Invalid expression in brackets!";
			return false;
		}
		if (!areBracketsCorrect(str))
		{
			throw "Invalid Parentheses";
			return false;
		}
	}
	return true;
}

int Parser::priority(string c)
{
	if (c == "~")
		return 4;
	else if (c == "*" || c == "/" || c == "%")
		return 3;
	else if (c == "+" || c == "-")
		return 2;
	else if (c == "#" || c == "=" || c == "read" || c == "print")
		return 1;
	else
		return -1;
}


bool Parser::isCorrectLine(string str)
{
	removeSpaces(str);
	int j = 0;
	if (!isLetter(str[j]))
	{
		throw "The line does not start with letter!";
		return false;
	}
	if (isOperation(str[str.size() - 1]))
	{
		throw "Operation at the end of the line!";
		return false;
	}
	if (!containsSubstring(str, "="))
	{
		if (!containsSubstring(str, "read") && !containsSubstring(str, "print"))
		{
			throw "No equality operator, read or print at the line!";
			return false;
		}
		if (containsSubstring(str, "read") && containsSubstring(str, "print"))
		{
			throw "Both read and print at the line!";
			return false;
		}
	}
	if (!isValidExpression(str))
	{
		return false;
	}
	return true;
}

bool Parser::checkOneTypeBrackets(char c1, char c2)
{
	if ((c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']'))
	{
		return true;
	}
	return false;
}

bool Parser::areBracketsCorrect(string str)
{
	stack<char> openingBrackets;

	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (isOpeningBracket(str[i]))
		{
			openingBrackets.push(str[i]);
		}
		if (isClosingBracket(str[i]))
		{
			if (openingBrackets.size() > 0)
			{
				char top = openingBrackets.top();
				if (!checkOneTypeBrackets(top, str[i]))
				{
					return false;
				}
				openingBrackets.pop();
			}
			else return false;
		}
	}
	if (openingBrackets.size() == 0)
	{
		return true;
	}
	else return false;
}

bool Parser::countOperators(vector<string> v)
{
	int count = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if ((v[i].compare("=") == 0) || (v[i].compare("read") == 0) || (v[i].compare("print") == 0))
			count++;
	}
	if (count == 1)
		return true;
	else
		return false;
}

void Parser::removeSpaces(string& str)
{
	str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}

void Parser::removeSpacesAfter(string& str, int& index)
{
	while (str[index] == ' ')
	{
		++index;
	}
}

string Parser::getString(char x)
{
	string s(1, x);

	return s;
}

unsigned int Parser::convertFromStringToInt(string s)
{
	unsigned int result = 0;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		result = result * 10 + (unsigned int(s[i]) - 48);
	}
	return result;

}

bool Parser::isOperation(char c)
{
	if (c == '+' || c == '-' || c == '/' || c == '%' || c == '*' || c == '=' || c == '~')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Parser::isLetter(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return true;
	}
	return false;
}

bool Parser::isBracket(char c)
{
	if (c == '[' || c == ']' || c == '(' || c == ')')
	{
		return true;
	}
	return false;
}

bool Parser::isNumber(char c)
{
	if (isdigit(c))
	{
		return true;
	}
	return false;
}

bool Parser::containsSubstring(const string& str, const string& sub)
{
	if (sub.length() == 0) return false;
	int count = 0;
	for (size_t offset = str.find(sub); offset != string::npos;
		offset = str.find(sub, offset + sub.length()))
	{
		++count;
	}
	if (count > 0)
	{
		return true;
	}
	return false;
}

bool Parser::isOpeningBracket(char c)
{
	if (c == '(' || c == '[')
	{
		return true;
	}
	return false;
}

bool Parser::isClosingBracket(char c)
{
	if (c == ')' || c == ']')
	{
		return true;
	}
	return false;
}

