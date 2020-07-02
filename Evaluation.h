#ifndef EVALUATION_H
#define EVALUATION_H

#include "Tree.h"
#include <map>
#include <vector>

class Evaluation
{
private:
	map<string, unsigned int> constants;
	map<string, Tree> functions;

	void insertFunctionInMap(string, Tree);
	Tree getFunctionFromMap(string);
	bool containsKeyInFunctionsMap(string);

	void insertElemInMap(string, int);
	unsigned int getValueByKey(string);
	bool containsKeyInConstantsMap(string);
	void deleteElemFromConstMap(string);

	string input();

	void evalIfOperation(pair<int, bool>&, Position);
	void evalIfLeaf(pair<int, bool>&, Position);
	pair<int, bool> evaluateNumTree(Position);
	pair<int, bool> evalFunc(Position, int);

public:
	void eval(Position, Tree&);
};
#endif // !EVALUATION_H