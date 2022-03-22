using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include "Utils.h"
#include <stdio.h>
#include <map>

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

void crackVigenereCypher(char cypher[], char key[])
{
	char plainText[1000];
	strcpy_s(plainText, cypher);

	//For each position in the cypher
	int cypherPos = 0;
	int keyPos = 0;

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

	char result[35];
	strncpy_s(result, plainText, 30);
	cout << result << endl;
}

void crackCypherTwo()
{
	//Get cypher
	char file[] = "cexercise2";
	char cypher[1000];
	strncpy_s(cypher, getCypher(file), 1000);
	
	//Define key and plainText
	char key[] = "TESSOFTHEDURBERVILLES";
	crackVigenereCypher(cypher, key);
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

map<char, int> createFrequencyTable(char cypher[], int keyPosition, int keySize)
{
	map<char, int> table; //0-A, 1-B etc.
	clearTable(table);

	for (int i = keyPosition; i < strlen(cypher); i += keySize)
		table[cypher[i]]++;

	return table;
}

map<char, float> percentageFromFrequency(map<char, int> frequency)
{
	float total = 0;
	map<char, float> percentage;
	clearTable(percentage);

	for (char c = 'A'; c <= 'Z'; c++)
		total += frequency[c];

	for (char c = 'A'; c <= 'Z'; c++)
		percentage[c] = (frequency[c] * 100) / total;

	return percentage;
}

void crackVigenereCypherNoKey(char cypher[], int keyPosition, int keySize)
{
	map<char, int> frequency = createFrequencyTable(cypher, keyPosition, keySize);
	map<char, float> percentage = percentageFromFrequency(frequency);

	cout << "Frequency in the English language:\n";
	map<char, float> englishFreq = getEnglishFrequency();
	for (char c = 'A'; c <= 'Z'; c++)
		printf("%c %.2f\n", c, englishFreq[c]);

	cout << "Frequency in cypher for position " << keyPosition << " in the key:\n";
	for (char c = 'A'; c <= 'Z'; c++)
		printf("%c %.2f\n", c, percentage[c]);

	cout << endl;

	//Define key and plainText
	char key[] = "NKRQHL";
	crackVigenereCypher(cypher, key);
}

void crackCypherThree()
{
	//Get cypher
	char file[] = "cexercise3";
	char cypher[1000];
	strncpy_s(cypher, getCypher(file), 1000);

	crackVigenereCypherNoKey(cypher, 0, 6);
}


int main()
{
	cout << "Cypher 1: " << endl;
    crackCypherOne();

	cout << endl << "Cypher 2: " << endl;
	crackCypherTwo();
	
	cout << endl << "Cypher 3:" << endl;
	crackCypherThree();

    return 0;
}