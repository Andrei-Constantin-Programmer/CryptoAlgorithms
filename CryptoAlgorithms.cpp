using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include "Utils.h"
#include <stdio.h>
#include <map>
#include "VariadicTable.h"


#pragma region Caesar_Cypher
char* caesarShift(char cypher[])
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

	cout << "Here are all possible permutations. Pick the one that looks legible\n";
	int number = 1;
	do
	{
		strcpy_s(auxCypher, caesarShift(auxCypher));
		printf("%d. %s\n", number, auxCypher);
		number++;
	} while (strcmp(cypher, auxCypher));

}

#pragma endregion Caesar_Cypher

#pragma region Vigenere_With_Key
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

#pragma endregion Vigenere_With_Key

#pragma region Frequency_Tables
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

map<char, float> createPercentageTable(char cypher[], int keyPosition, int keySize)
{
	return percentageFromFrequency(createFrequencyTable(cypher, keyPosition, keySize));
}

void printFrequencyTable(map<char, float> frequency)
{
	for (char c = 'A'; c <= 'Z'; c++)
		printf("  %c  ", c);
	cout << endl;
	for (char c = 'A'; c <= 'Z'; c++)
		printf("%.2f ", frequency[c]);
	cout << endl;
}

void printFrequencyTables(map<char, float> frequency)
{
	map<char, float> englishFreq = getEnglishFrequency();
	cout << "Frequency in the English language:\n";
	printFrequencyTable(englishFreq);

	cout << "Frequency in cypher:\n";
	printFrequencyTable(frequency);
}

#pragma endregion Frequency_Tables

#pragma region Vigenere_Without_Key
char* createKeyVigenere(char cypher[], int keySize)
{
	//char key[100];
	char key[] = "NKRQHL";
	map<char, float> frequency;

	frequency = createPercentageTable(cypher, 0, keySize);

	printFrequencyTables(frequency);
	cout << endl;

	return key;
}

void crackVigenereCypherNoKey(char cypher[], int keySize)
{
	char key[100];
	strcpy_s(key, createKeyVigenere(cypher, keySize));
	
	//crackVigenereCypher(cypher, key);
}


void crackCypherThree()
{
	//Get cypher
	char file[] = "cexercise3";
	char cypher[1000];
	strncpy_s(cypher, getCypher(file), 1000);

	crackVigenereCypherNoKey(cypher, 6);
}

#pragma endregion Vigenere_Without_Key





int main()
{
	bool play = true;
	while (play)
	{
		cout << "\nWhat cypher do you want to solve (1-7)? Enter 0 to quit the application.\nChoice: ";
		int option;
		cin >> option;
		switch (option)
		{
			case 0:
				cout << "Goodbye!\n";
				play = false;
				break;
			case 1:
				cout << "Cypher 1: " << endl;
				crackCypherOne();
				break;
			case 2:
				cout << endl << "Cypher 2: " << endl;
				crackCypherTwo();
				break;
			case 3:
				cout << endl << "Cypher 3:" << endl;
				crackCypherThree();
				break;
			default:
				cout << "Sorry, that cypher does not exist";
		}
	}


    return 0;
}