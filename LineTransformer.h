#ifndef LineTransformer_H
#define LineTransformer_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class LineTransformer
{
public:
	LineTransformer();
	LineTransformer(string);

	vector<string> getLine();

	void replaceFunctionEqualSign(vector<string>&);   //replace '=' with '#' in definition of function
	void putFunctionEvaluationSymbol(vector<string>&);  //puts '~' in front of functions that have to be evaluated (F[5] -> ~F[5])
	void appendNameOfFunctionToArgument(vector<string>&);

private: 
	vector<string> line;

	void makeLine(string);

	void insertInVector(int, const string&, vector<string>& v);
	string makeWord(string, int);
	string makeWordOfSmallLetters(const string, int);
	string makeWordOfCapitalLetters(const string, int);
	string makeNumber(const string, int);

};
#endif // !"LineTransformer"

