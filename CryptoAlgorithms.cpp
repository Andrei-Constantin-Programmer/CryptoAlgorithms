using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include "Utils.h"
#include <stdio.h>

char* shift(char cypher[])
{
	//Shift the cypher's alphabet to the left
	for (int i = 0; i < strlen(cypher); i++)
		if (cypher[i] == 'A')
			cypher[i] = 'Z';
		else
			cypher[i]--;

	return cypher;
}

void crackCypherOne()
{
	//Get cypher
	char file[] = "cexercise1";
	char cypher[35];
	strncpy_s(cypher, getCypher(file), 30);

	//Copy cypher
	char auxCypher[35];
	strcpy_s(auxCypher, cypher);

	//Create all of the possible shifts 
	int number = 1;
	do
	{
		strcpy_s(auxCypher, shift(auxCypher));
		printf("%d. %s\n", number, auxCypher);
		number++;
	} while (strcmp(cypher, auxCypher));
}

void crackCypherTwo()
{
	//Get cypher
	char file[] = "cexercise2";
	char cypher[35];
	strncpy_s(cypher, getCypher(file), 30);
	
	//Define key and plainText
	char key[] = "TESSOFTHEDURBERVILLES";
	char plainText[35];
	strcpy_s(plainText, cypher);
	
	//For each position in the cypher
	int cypherPos = 0;
	int keyPos = 0;

	cout << cypher << endl;
	
	while (cypherPos < strlen(cypher))
	{
		//Get the corresponding value by subtracting the key value from the cypher value.
		char value = cypher[cypherPos] - key[keyPos] + 'A';
		
		//If the value is 'negative', add '26'
		if (value < 'A')
			value += 26;

		plainText[cypherPos] = value;

		cypherPos++;
		keyPos++;
		if (keyPos >= strlen(key))
			keyPos = 0;
	}

	cout << plainText << endl;
}

int main()
{
	cout << "Cypher 1: " << endl;
    crackCypherOne();

	cout << endl << "Cypher 2: " << endl;
	crackCypherTwo();

    return 0;
}