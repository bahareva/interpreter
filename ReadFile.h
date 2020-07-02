#ifndef ReadFile_H
#define ReadFile_H

#include <iostream>
#include <fstream>
using namespace std;

class ReadFile
{
public:
	ReadFile();
	ReadFile(string);
	ReadFile(const ReadFile&);
	
	string getFileName();
	void setFileName(string);
	void executeFile();

private:
	string fileName;

};

#endif // !ReadFile_H

