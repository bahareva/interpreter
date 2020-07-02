#include "Tree.h"
#include "ReadFile.h"
#include "Parser.h"
#include "Evaluation.h"
#include "LineTransformer.h"
#include <exception>

void Evaluation::insertFunctionInMap(string key, Tree t)
{
	if (!containsKeyInFunctionsMap(key))
		functions.insert(pair<string, Tree>(key, t));
	else
		throw "Function already exist!";
}

Tree Evaluation::getFunctionFromMap(string key)
{
	map<string, Tree>::iterator it;
	it = functions.find(key);

	if (it == functions.end())
		throw "Function doesn't exist!";
	else
		return it->second;
}

bool Evaluation::containsKeyInFunctionsMap(string key)
{
	if (functions.count(key) > 0)
	{
		return true;
	}
	return false;
}

void Evaluation::insertElemInMap(string key, int value)
{
	map<string, unsigned int>::iterator i = constants.find(key);
	if (i == constants.end())
	{
		constants.insert(pair<string, int>(key, value));
	}
	else
	{
		try
		{
			deleteElemFromConstMap(key);
		}
		catch (const char* msg)
		{
			cout << msg << endl;
		}
		constants.insert(pair<string, int>(key, value));
	}
}

void Evaluation::deleteElemFromConstMap(string key)
{
	if (containsKeyInConstantsMap(key))
	{
		map<string, unsigned int>::iterator it;
		it = constants.find(key);
		constants.erase(it);
	}
	else
	{
		throw "Element does't exist in map to be deleted!";
	}
}

unsigned int Evaluation::getValueByKey(string key)
{
	if (containsKeyInConstantsMap(key))
	{
		return constants[key];
	}
	else
	{
		throw "Key-value pair doesn't exist in map!";
	}
}

bool Evaluation::containsKeyInConstantsMap(string key)
{
	if (constants.count(key) > 0)
	{
		return true;
	}
	return false;
}


string Evaluation::input()
{
	string result;
	char c;
	cin.get(c);
	while (c != '\n')
	{
		result.push_back(c);
		cin.get(c);
	}
	return result;
}

pair<int, bool> Evaluation::evalFunc(Position p, int valueOfarg)
{
	insertElemInMap(p.middle().getData(), valueOfarg);
	pair<int, bool> result = evaluateNumTree(p.right());
	try
	{
		deleteElemFromConstMap(p.middle().getData());
	}
	catch (const char* msg)
	{
		cout << msg << endl;
		result.first = -1;
		result.second = 0;
		return result;
	}
	return result;
}

void Evaluation::evalIfLeaf(pair<int, bool>& result, Position p)
{
	Parser par;
	if (p.getData()[0] >= 'a' && p.getData()[0] <= 'z' && p.left().empty() && p.middle().empty() && p.right().empty())
	{
		if (containsKeyInConstantsMap(p.getData()))
		{
			result.first = getValueByKey(p.getData());
		}
		else
		{
			throw "Undefined expression!";
			result.first = -1;
			result.second = 0;
		}
	}
	if (par.isNumber(p.getData()[0]) && p.left().empty() && p.middle().empty() && p.right().empty())
	{
		result.first = par.convertFromStringToInt(p.getData());;
		result.second = 1;
	}
}

void Evaluation::evalIfOperation(pair<int, bool>& result, Position p)
{
	Parser par;
	if (par.isOperation(p.getData()[0]))
	{
		pair<int, bool> l_val = evaluateNumTree(p.left());
		pair<int, bool> r_val = evaluateNumTree(p.right());
		if (l_val.second == 0 || r_val.second == 0)
		{
			result.first = -1;
			result.second = 0;
		}
		if (p.getData() == "+")
		{
			result.first = l_val.first + r_val.first;
			result.second = 1;
		}
		if (p.getData() == "-")
		{
			result.first = l_val.first - r_val.first;
			result.second = 1;
		}
		if (p.getData() == "*")
		{
			result.first = l_val.first * r_val.first;
			result.second = 1;
		}
		if (p.getData() == "/")
		{
			if (r_val.first == 0)
			{
				throw "Division by zero!";
				result.first = -1;
				result.second = 0;
			}
			else
			{
				result.first = l_val.first / r_val.first;
				result.second = 1;
			}
		}
		if (p.getData() == "%")
		{
			if (r_val.first == 0)
			{
				throw "Modul by zero!";
				result.first = -1;
				result.second = 0;
			}
			else
			{
				result.first = l_val.first % r_val.first;
				result.second = 1;
			}
		}
	}
}


pair<int, bool> Evaluation::evaluateNumTree(Position p)
{
	pair<int, bool> result;
	result.first = -1;
	result.second = 1;
	if (p.empty())
	{
		result.first = -1;
		result.second = 0;
		return result;
	}

	evalIfLeaf(result, p);

	if (p.getData() == "~" && !p.left().empty())
	{
		Tree tree;
		try
		{
			tree = getFunctionFromMap(p.left().getData());
		}
		catch (const char* msg)
		{
			cout << msg << endl;
			result.first = -1;
			result.second = 0;
			return result;
		}
		int arg = evaluateNumTree(p.right()).first;
		if (arg < 0)
		{
			throw "Can't evaluate expression in function!";
			result.first = -1;
			result.second = 0;
			return result;
		}
		else
		{
			result = evalFunc(tree.rootPos(), arg);
			if (result.first < 0)
			{
				throw "Negative result!";
				result.first = -1;
				result.second = 0;
				return result;
			}
			else
			{
				return result;
			}
		}
	}

	evalIfOperation(result, p);
	return result;
}

void Evaluation::eval(Position p, Tree& t)
{
	Parser par;
	if (p.getData() == "=")
	{
		pair<int, bool>  result;
		result = evaluateNumTree(p.right());
		if (result.first < 0)
			throw "Negative result!";
		else
			insertElemInMap(p.left().getData(), result.first);
	}
	else if (p.getData() == "#")
	{
		try
		{
			insertFunctionInMap(p.left().getData(), t);
		}
		catch (const char* msg)
		{
			cout << msg << endl;
			return;
		}
	}
	else if (p.getData() == "print")
	{
		pair<int, bool>  result;
		result = evaluateNumTree(p.right());
		if (result.first < 0)
			throw "Can't print the result!";
		else 
			cout << "Result = " << result.first << endl;
	}
	else if (p.getData() == "read")
	{
		string s = input();
		LineTransformer l(s);
		vector<string> v = l.getLine();
		Tree tree(v);
		pair<int, bool> res = evaluateNumTree(tree.rootPos());
		insertElemInMap(p.right().getData(), res.first);
	}
}
