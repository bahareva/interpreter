#include <iostream>
#include "ReadFile.h"
#include "LineTransformer.h"
#include <fstream>

using namespace std;

int main()
{
	ReadFile f("file.txt");
	f.executeFile();
}