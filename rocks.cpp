#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int manageOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum);

int main ()
{
	const int MAXWORDS = 11000;
	char wordList[MAXWORDS][MAXWORDLEN+1]; //Creates the array of all possible words

	int nWords = loadWords(wordList, MAXWORDS); //Number of words in an array
  
	if (nWords < 1)
	{
		cout << "No words were loaded, so I can't play the game." << endl;
		return 0;
	}

	cout << "How many rounds do you want to play? ";

	int numberOfRounds = 0;
	cin >> numberOfRounds;
	cin.ignore(10000, '\n');

	if (numberOfRounds <= 0) //zero is not positive
    {
    	cout << "The number of rounds must be positive." << endl;
		return 0;
    }

  	cout << endl;
  	
  	//Initializes all variables before the for-loop
  	int score = 0;
  	double average = 0;
  	int mininum = 50000;
  	int maximum = 0;
  	double totalScore = 0;
  	int randomNumber = 0;
  	int numberOfLetters = 4;

	for (int i = 1; i <= numberOfRounds; i++)
	{
		cout << "Round " << i << endl;
		randomNumber = randInt(0, nWords - 1);
		numberOfLetters = strlen(wordList[randomNumber]);
		cout << "The secret word is " << numberOfLetters << " letters long." << endl;
		
		score = manageOneRound(wordList, nWords, randomNumber);
		
		if (score == -1)
		{
			cout << "The function manageOneRound is invalid." << endl;
			return 0; //this is in FAQ
		}
		else if (score == 1)
			cout << "You got it in 1 try." << endl;
		else
			cout << "You got it in " << score << " tries." << endl;
		
		totalScore += score;
		
		if (score > maximum) //Adjusts maximum and mininum scores after each round
			maximum = score;
		if (score < mininum)
			mininum = score;
		
		cout.setf(ios::fixed);
		cout.precision(2);
		
		average = (totalScore/i);
		
		cout << "Average: " << average << ", mininum: " << mininum << ", maximum: " << maximum << endl << endl;;
	}
}

//This function returns the score for the round
int manageOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum)
{

	if (nWords <= 0 || wordnum < 0 || wordnum >= nWords) //Checks valid nWords
		return -1;

	char secretWord[7];
	strcpy(secretWord, words[wordnum]);

	int restart = 0;
	int scoreCounter = 1;
	char inputWord[7];
	
	for (;;) //infinite loop until the probe word is the correct word
	{
		cout << "Probe word: ";
		cin.getline(inputWord, 500);
		
		if (strcmp(secretWord, inputWord) == 0) //If secret and input words are the same
			break;
	
		else
		{
			//This loop determines if the inputWord is not all lower case letters
			for (int j = 0;; j++)
			{
				if (!islower(inputWord[j]) && inputWord[j] != '\0')
					restart = -1;
				if (inputWord[j] == '\0')
					break;
			}
			
			if (restart == -1)
			{
				restart = 0;
				cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
				continue;
			}
			
			//Checks if the length of the word is 4-6 charactesr long
			if (strlen(inputWord) < 4 || strlen(inputWord) > 6)
			{
				cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
				continue;
			}
			
			for (int k = 0; k <= nWords; k++) //Checks if the inputWord is any of the words in the wordlist
			{
				if (strcmp(inputWord, words[k]) == 0)
					break;
				else if (k != nWords)
					continue;
				else //when k == nWords, then the loop has cycled through the entire wordList
					restart = -2;
			}
			
			if (restart == -2)
			{	
				restart = 0;
				cout << "I don't know that word." << endl;
				continue;
			}
			
			scoreCounter++;
			int nRocks = 0; 
			int nPebbles = 0;
			
			for (int i = 0; i < 6; i++) //Checks for number of rocks
   			{
				if (inputWord[i] != '\0' && secretWord[i] != '\0' && inputWord[i] == secretWord[i])
					nRocks++;
				else if (inputWord[i] == '\0' || secretWord[i] == '\0')
					break;
				
				//If both conditions fail, loop reiterates again
			}  
			
			int x = 0; //placeholder
		
			for (int j = 0; j < 6; j++) //Checks for number of pebbles
			{
				if (inputWord[j] != '\0' && secretWord[j] != '\0' && inputWord[j] == secretWord[j]) //Does not count rocks
					continue;
				if (inputWord[j] == '\0')
					break;
				else
				{
					for (int k = 0; secretWord[k] != '\0'; k++) //Checks for correctly repeated letter
					{
						//Each condition checks for a specific position of inputWord
						//If a letter previous to the posisition has already incremented pebbles,
						//Then pebbles will not be incremented again
						if (inputWord[j] == secretWord[k] && j != k)
						{
							x = j;
							
							if (inputWord[k] == secretWord[k]) //Does not count rocks
								continue;
								
							if (x == 5 && inputWord[x-5] != secretWord[k] && inputWord[x-4] != secretWord[k] && inputWord[x-3] != secretWord[k] && inputWord[x-2] != secretWord[k] && inputWord[x-1] != secretWord[k] && k != 5)
							{
								nPebbles++;
								break;
							}
							else if (x == 4 && inputWord[x-4] != secretWord[k] && inputWord[x-3] != secretWord[k] && inputWord[x-2] != secretWord[k] && inputWord[x-1] != secretWord[k] && k != 4)
							{
								nPebbles++;
								break;
							}
							else if (x == 3 && inputWord[x-3] != secretWord[k] && inputWord[x-2] != secretWord[k] && inputWord[x-1] != secretWord[k] && k != 3)
							{
								nPebbles++;
								break;
							}
							else if (x == 2 && inputWord[x-2] != secretWord[k] && inputWord[x-1] != secretWord[k] && k != 2)
							{
								nPebbles++;
								break;
							}
							else if (x == 1 && inputWord[x-1] != secretWord[k] && k != 1)
							{
								nPebbles++;
								break;
							}
							else if (x == 0 && k != 0)
							{
								nPebbles++;
								break;
							}
							else
								break;
						}	
					}
				}
			}
			cout << "Rocks: " << nRocks << ", Pebbles: " << nPebbles << endl;	
		}
	}
	return scoreCounter;
}


