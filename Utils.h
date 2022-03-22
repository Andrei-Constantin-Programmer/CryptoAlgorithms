using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <sstream>
#include <map>

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

map<char, float> getEnglishFrequency()
{
	return {
		{'A', 8.2f},
		{'B', 1.5f},
		{'C', 2.7f},
		{'D', 4.7f},
		{'E', 13.0f},
		{'F', 2.2f},
		{'G', 2.0f},
		{'H', 6.2f},
		{'I', 6.9f},
		{'J', 0.16f},
		{'K', 0.81f},
		{'L', 4.0f},
		{'M', 2.7f},
		{'N', 6.7f},
		{'O', 7.8f},
		{'P', 1.9f},
		{'Q', 0.11f},
		{'R', 5.9f},
		{'S', 6.2f},
		{'T', 9.6f},
		{'U', 2.7f},
		{'V', 0.97f},
		{'W', 2.4f},
		{'X', 0.15f},
		{'Y', 2.0f},
		{'Z', 0.078f},
	};
}

void clearTable(map<char, int> table)
{
	table = {
		{'A', 0},
		{'B', 0},
		{'C', 0},
		{'D', 0},
		{'E', 0},
		{'F', 0},
		{'G', 0},
		{'H', 0},
		{'I', 0},
		{'J', 0},
		{'K', 0},
		{'L', 0},
		{'M', 0},
		{'N', 0},
		{'O', 0},
		{'P', 0},
		{'Q', 0},
		{'R', 0},
		{'S', 0},
		{'T', 0},
		{'U', 0},
		{'V', 0},
		{'W', 0},
		{'X', 0},
		{'Y', 0},
		{'Z', 0},
	};
}

void clearTable(map<char, float> table)
{
	table = {
		{'A', 0},
		{'B', 0},
		{'C', 0},
		{'D', 0},
		{'E', 0},
		{'F', 0},
		{'G', 0},
		{'H', 0},
		{'I', 0},
		{'J', 0},
		{'K', 0},
		{'L', 0},
		{'M', 0},
		{'N', 0},
		{'O', 0},
		{'P', 0},
		{'Q', 0},
		{'R', 0},
		{'S', 0},
		{'T', 0},
		{'U', 0},
		{'V', 0},
		{'W', 0},
		{'X', 0},
		{'Y', 0},
		{'Z', 0},
	};
}
