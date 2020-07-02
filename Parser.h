#ifndef Parser_H
#define Parser_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Parser
{
public:
	bool checkNumbers(string);
	bool checkOneTypeBrackets(char, char);
	bool containsSubstring(const string&, const string&);
	bool isOpeningBracket(char);
	bool isClosingBracket(char);
	bool isOperation(char);
	bool isLetter(char);
	bool isNumber(char);
	bool isBracket(char);
	bool isCorrectLine(string);
	bool checkLowercaseLetters(string);
	bool checkUppercaseLetters(string);
	bool isVectorCorrect(vector<string>);
	bool isValidExpression(string);
	bool areBracketsCorrect(string);
	bool countOperators(vector<string>);

	void removeSpaces(string&);
	void removeSpacesAfter(string&, int&);

	unsigned int convertFromStringToInt(string);
	int priority(string);
	string getString(char);
};

#endif // !Parser_H

