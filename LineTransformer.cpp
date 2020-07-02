#include "LineTransformer.h"
#include "Parser.h"

LineTransformer::LineTransformer():line(0)
{}

LineTransformer::LineTransformer(string _line):LineTransformer()
{
	makeLine(_line);
}

vector<string> LineTransformer::getLine()
{
	return line;
}

void LineTransformer::makeLine(string str)
{
	Parser p;
	int i = 0;
	int len;
	string word;
	int lenOfStr = str.size();
	while (i < lenOfStr)
	{
		if (str[i] == ' ')
		{
			p.removeSpacesAfter(str, i);
		}
		if (p.isOperation(str[i]))
		{
			this->line.push_back(p.getString(str[i]));
			i++;
		}
		else if (p.isLetter(str[i]) || isdigit(str[i]))
		{
			try
			{
				word = makeWord(str, i);
			}
			catch (const char* msg)
			{
				cout << msg << endl;
			}
			this->line.push_back(word);
			len = word.size();
			i += len;
		}
		else if (p.isBracket(str[i]))
		{
			this->line.push_back(p.getString(str[i]));
			i++;
		}
	}
}


string LineTransformer::makeWord(string str, int i)
{
	string res;
	if (str[i] >= 'a' && str[i] <= 'z')
	{
		res = makeWordOfSmallLetters(str, i);
	}
	else if (str[i] >= 'A' && str[i] <= 'Z')
	{
		res = makeWordOfCapitalLetters(str, i);
	}
	else if (str[i] >= '0' && str[i] <= '9')
	{
		res = makeNumber(str, i);
	}
	else
	{
		throw "Invalid input in file!";
	}
	return res;
}

string LineTransformer::makeWordOfSmallLetters(string str, int j)
{
	string result = "";
	int i = j;
	while (str[i] >= 'a' && str[i] <= 'z')
	{
		result.push_back(str[i]);
		i++;
	}
	return result;
}

string LineTransformer::makeWordOfCapitalLetters(string str, int j)
{
	string result = "";
	int i = j;
	while (str[i] >= 'A' && str[i] <= 'Z')
	{
		result.push_back(str[i]);
		i++;
	}
	return result;
}

string LineTransformer::makeNumber(string str, int j)
{
	string result = "";
	int i = j;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result.push_back(str[i]);
		i++;
	}
	return result;
}

void LineTransformer::insertInVector(int position, const string& val, vector<string>& v)
{
	auto itPos = v.begin() + position;
	auto newIt = v.insert(itPos, val);
}

void LineTransformer::replaceFunctionEqualSign(vector<string>& v)
{
	if (v[0][0] >= 'A' && v[0][0] <= 'Z')
	{
		int len = v.size();
		for (int i = 0; i < len; i++)
		{
			if (v[i] == "=")
			{
				v[i] = "#";
			}
		}
	}
}

void LineTransformer::putFunctionEvaluationSymbol(vector<string>& v)
{
	Parser p;
	int len = v.size();
	for (int i = 1; i < len; i++)
	{
		if (p.checkUppercaseLetters(v[i]))
		{
			insertInVector(i, "~", v);
			i++;
			len++;
		}
	}
}

void LineTransformer::appendNameOfFunctionToArgument(vector<string>& v)
{
	Parser p;
	if (p.checkUppercaseLetters(v[0]))
	{
		string funcName = v[0];
		string argName = v[2];
		string newArg = v[2];
		newArg = newArg.append(funcName);
		for (unsigned int i = 0; i < v.size(); i++)
		{
			if (v[i].compare(argName) == 0)
			{
				v[i] = newArg;
			}
		}
	}
}
