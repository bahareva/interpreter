#include "ReadFile.h"
#include "Parser.h"
#include "LineTransformer.h"
#include "Tree.h"
#include "Evaluation.h"
#include <fstream>
#include <string>
#include <vector>


ReadFile::ReadFile()
{
	this->fileName = "";
}

ReadFile::ReadFile(string _fileName)
{
	this->fileName = _fileName;
}

ReadFile::ReadFile(const ReadFile& f)
{
	this->fileName = f.fileName;
}

string ReadFile::getFileName()
{
	return this->fileName;
}

void ReadFile::setFileName(string _fileName)
{
	this->fileName = _fileName;
}

void ReadFile::executeFile()
{
	string line = "";
	ifstream file;
	file.open(getFileName());

	if (!file) {
		cout << "Unable to open file";
		exit(1);
	}

	Parser p;
	Evaluation ev;

	int countLines = 1;
	while (getline(file, line))
	{
		cout << "Line: " << line << endl;
		bool result = false;
		//correctness of readed line
		try
		{
			result = p.isCorrectLine(line);
		}
		catch (const char* msg) {
			cout << "Syntax error in line #" << countLines << ": ";
			cout << msg << endl;
		}

		if (result)
		{
			//make vector of strings         
			LineTransformer l(line);
			vector<string> v = l.getLine();
			bool correctVector = false;
			//correctness of vector 
			try
			{
				correctVector = p.isVectorCorrect(v);
			}
			catch (const char* msg) {
				cout << "Syntax error in line #" << countLines << ": ";
				cout << msg << endl;
			}

			if (correctVector)
			{
				l.putFunctionEvaluationSymbol(v);
				l.replaceFunctionEqualSign(v);
				l.appendNameOfFunctionToArgument(v);
				Tree t(v);
				//make tree, calculate expression in tree and print the result
				try
				{
					ev.eval(t.rootPos(), t);
				}
				catch (const char* msg)
				{
					cout << "Syntax error in line #" << countLines << ": ";
					cout << msg << endl;
				}
			}
		}
		++countLines;
	}
	file.close();
}
