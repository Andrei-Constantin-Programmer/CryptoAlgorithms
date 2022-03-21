using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <sstream>

char* getCypher(char fileName[])
{
	stringstream dir; 
	dir << "G:\\.Year 2\\Term 2\\Cyber Security\\Crypto Assignment\\" << fileName << ".txt";
	ifstream f(dir.str());

	char cypher[1000];
	f.getline(cypher, 1000);
	f.close();

	return cypher;
}
