using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include "Utils.h"
#include <stdio.h>
#include <map>
#include "VariadicTable.h"

char alphabeticalOrder[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


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
//Create a map of frequencies based on the given cypher, key position and key size
map<char, int> createFrequencyTable(char cypher[], int keyPosition, int keySize)
{
	map<char, int> table; //0-A, 1-B etc.
	clearTable(table);

	for (int i = keyPosition; i < strlen(cypher); i += keySize)
		table[cypher[i]]++;

	return table;
}

//Create a map of percentages based on the map of frequencies given
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

//Print the given frequency table based on the frequency order
void printFrequencyTable(map<char, float> frequency, char frequencyOrder[])
{
	for (int i = 0; i < strlen(frequencyOrder); i++)
		printf("  %c   ", frequencyOrder[i]);
	cout << endl;
	for (int i = 0; i < strlen(frequencyOrder); i++)
		if(frequency[frequencyOrder[i]] < 10)
			printf(" %.2f ", frequency[frequencyOrder[i]]);
		else
			printf("%.2f ", frequency[frequencyOrder[i]]);
	cout << endl;
}

void printFrequencyTable(map<char, float> frequency)
{
	printFrequencyTable(frequency, alphabeticalOrder);
}


void printFrequencyTables(map<char, float> frequency, char frequencyOrder[])
{
	map<char, float> englishFreq = getEnglishFrequency();
	cout << "Frequency in the English language:\n";
	printFrequencyTable(englishFreq);

	cout << endl;

	cout << "Frequency in cypher:\n";
	printFrequencyTable(frequency, frequencyOrder);
}

void shiftFrequencyOrderRight(char order[])
{
	char last = order[strlen(order) - 1];
	for (int i = strlen(order) - 1; i > 0; i--)
		order[i] = order[i - 1];
	order[0] = last;
}

void shiftFrequencyOrderLeft(char order[])
{
	char first = order[0];
	for (int i = 0; i < strlen(order) - 1; i++)
		order[i] = order[i + 1];
	order[strlen(order)-1] = first;
}

#pragma endregion Frequency_Tables

#pragma region Vigenere_Without_Key
bool createKeyVigenere(char key[], char cypher[], int keySize)
{
	map<char, float> frequency;

	//Calculate the key letter for each key position
	for (int i = 0; i < keySize; i++)
	{
		cout << "Analysis for position " << i+1 << " in the key\n";
		//Create the table frequency
		frequency = createPercentageTable(cypher, i, keySize);
		char order[30];
		strcpy_s(order, alphabeticalOrder);
		
		bool cont = true;

		while (cont)
		{
			cout << endl;
			printFrequencyTables(frequency, order);
			
			cout << "\nEnter = if this is the right frequency table, - to shift left and + to shift right. Alternatively, enter 0 to quit to the main menu.\nChoice (+, -, =, 0): ";
			char option;
			cin >> option;
			switch (option)
			{
				case '=':
					cont = false;
					break;
				case '+':
					shiftFrequencyOrderRight(order);
					break;
				case '-':
					shiftFrequencyOrderLeft(order);
					break;
				case '0':
					return false;
					break;
				default:
					cout << "Unknown command, try again\n";
			}
		}

		key[i] = order[0];
		cout << "\nThe chosen letter for position " << i+1 << " in the key is " << key[i] << "\n\n";
	}

	return true;
}

void crackVigenereCypherNoKey(char cypher[], int keySize)
{
	char key[7];
	if (createKeyVigenere(key, cypher, keySize))
	{
		strncpy_s(key, key, 6);

		cout << "The key is: " << key << endl;

		cout << "The decyphered text is:\n";
		crackVigenereCypher(cypher, key);
	}
}


void crackCypherThree()
{
	//Get cypher
	char file[] = "cexercise3";
	char cypher[1000];
	strncpy_s(cypher, getCypher(file), 1000);

	crackVigenereCypherNoKey(cypher, 6);
}

int getKeySize(char cypher[])
{
	char smallCypher[1005];
	strcpy_s(smallCypher, cypher);
	int size = 0;

	int shifts = 0;
	int maxShifts = 0;
	int maxSimilarities = 0;

	for (int i = strlen(cypher) - 2, spaces=1; i >= 1; spaces++, i--)
	{
		shifts++;
		for (int j = 0; j < spaces; j++)
			smallCypher[j] = ' ';
		for (int j = spaces; j <= strlen(smallCypher)-spaces; j++)
			smallCypher[j] = cypher[j - spaces];

		int similarities = 0;

		for (int j = 0; j < strlen(smallCypher); j++)
			if(cypher[j]>='A' && cypher[j]<='Z')
				if (cypher[j] == smallCypher[j])
				{
					size++;
					similarities++;
				}
		
		if (similarities > maxSimilarities)
		{
			maxSimilarities = similarities;
			maxShifts = shifts;
		}
	}

	return maxShifts;
}

void crackCypherFour()
{
	//Get cypher
	char file[] = "cexercise4";
	char cypher[1000];
	strncpy_s(cypher, getCypher(file), 1000);

	int keySize = getKeySize(cypher);

	cout << "The key size is " << keySize << "\n\n";

	crackVigenereCypherNoKey(cypher, keySize);
}

#pragma endregion Vigenere_Without_Key

#pragma region Transposition

void createTranspositionTable(char cypher[], int columns)
{
	char table[1000][10];

	int line = 0, col = 0;
	int lines = strlen(cypher) / columns;

	for (int i = 0; i < strlen(cypher); i++)
	{
		table[line][col] = cypher[i];
		line++;
		if (line >= lines)
		{
			col++;
			line=0;
		}
	}

	char result[31];
	int resPos = 0;
	bool finished = false;

	cout << "For " << columns << " columns:\n";
	for (int i = 0; i < lines && !finished; i++)
	{
		for (int j = 0; j < columns && !finished; j++)
		{
			result[resPos] = table[i][j];
			resPos++;
			if (resPos > 30)
				finished=true;
		}
	}

	strncpy_s(result, result, 30);
	cout << result << endl;
}

void crackCypherFive()
{
	char file[] = "cexercise5";
	char cypher[1000];
	strncpy_s(cypher, getCypher(file), 1000);

	createTranspositionTable(cypher, 4);
	cout << endl;
	createTranspositionTable(cypher, 5);
	cout << endl;
	createTranspositionTable(cypher, 6);
	cout << endl;

}

#pragma endregion


int main()
{
	bool play = true;
	while (play)
	{
		cout << "\nWhat cypher do you want to solve (1-7)? Enter 0 to quit the application.\nChoice (0-7): ";
		int option;
		cin >> option;
		switch (option)
		{
			case 0:
				cout << "Goodbye!\n";
				play = false;
				break;
			case 1:
				cout << "Cypher 1:\n\n";
				crackCypherOne();
				break;
			case 2:
				cout << "Cypher 2:\n\n";
				crackCypherTwo();
				break;
			case 3:
				cout << "Cypher 3:\n\n";
				crackCypherThree();
				break;
			case 4:
				cout << "Cypher 4:\n\n";
				crackCypherFour();
				break;
			case 5:
				cout << "Cypher 5:\n\n";
				crackCypherFive();
				break;
			default:
				cout << "Sorry, that cypher does not exist";
		}
	}


    return 0;
}