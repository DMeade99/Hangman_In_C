/*
 * File Name: hangman.c
 * Author: Daryl Meade
 * Assignment: Project 1
 * Description: Function definitions for hangman game
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "hangman.h"

struct hangman
{
	char** puzzleWords;
	int numberOfPuzzles;
	char* currentPuzzle;
	char* guessedWord;
	bool gameOver;
	bool gameWon;
	int missedGuesses;
};

Hangman createHangmanGame(char *puzzleFile)
{
    // Initialize Hangman variables
    Hangman hangmanGame = malloc(sizeof *hangmanGame);
    hangmanGame->currentPuzzle = malloc(31 * sizeof(char));
    hangmanGame->guessedWord = malloc(31 * sizeof(char));
    
    // Open puzzleFile
    FILE *fin;
    fin = fopen(puzzleFile, "r");
    if (fin == NULL)
    {
        perror("Could not open file\n");
        exit(EXIT_FAILURE);
    }
    
    // Establish variables for file I/O
    char line[32];
    char temp[32];
    char *token;
    int rows = 0;
    
    // Fill numberOfPuzzles from file
    fseek(fin, 0, SEEK_SET);
    rows = atof(fgets(line, 32, fin));
    
    hangmanGame->numberOfPuzzles = rows;
    
    // Allocate memory for 2D char array
    hangmanGame->puzzleWords = (char **) malloc (rows * sizeof(char *));
    for (int a = 0; a < rows; a++)
    {
        hangmanGame->puzzleWords[a] = (char *) malloc (32 * sizeof(char));
    }
    
    // Populate 2D char array
    for (int a = 0; a < rows; a++)
    {
        fgets(line, 31, fin);
        strcpy(temp, line);
        token = strtok(temp, "\n\r");
        strcpy(hangmanGame->puzzleWords[a], token);
        
    }
    
    
    // Close puzzleFile    
    fclose(fin);
    
    return hangmanGame;
}

void newHangmanPuzzle(Hangman currentHangmanGame)
{
    currentHangmanGame->currentPuzzle = malloc(31 * sizeof(char));
    currentHangmanGame->guessedWord = malloc(31 * sizeof(char));
    for (int a = 0; a < 32; a++)
    {
        currentHangmanGame->guessedWord[a] = '\0';
        currentHangmanGame->currentPuzzle[a] = '\0';
    }  
    
    
    // Generate a random number
    int random;
    srand(time(NULL));
    random = (rand() % currentHangmanGame->numberOfPuzzles);
    
    // Select random puzzle as next puzzle
    strcpy(currentHangmanGame->currentPuzzle, currentHangmanGame->puzzleWords[random]);
    
    // Determine length of current puzzle
    int length = strlen(currentHangmanGame->currentPuzzle);
   
    for (int a = 0; a < length; a++)
    {
        currentHangmanGame->guessedWord[a] = '_';
    }
    
   // Clear arrays
    
    // Set guesses to zero
    currentHangmanGame->missedGuesses = 0;
    currentHangmanGame->gameOver = 0;
    currentHangmanGame->gameWon = 0;
    
}

void loadPuzzleFile(Hangman currentHangmanGame, char *puzzleFile)
{
    // Free previous array of puzzles
    free(currentHangmanGame->currentPuzzle);
    free(currentHangmanGame->guessedWord);
    free(currentHangmanGame->puzzleWords);
    for(int a =0; a < currentHangmanGame->numberOfPuzzles; a++)
    {
        free(currentHangmanGame->puzzleWords[a]);        
    }
    
    // Open puzzleFile
    FILE *fin;
    fin = fopen(puzzleFile, "r");
    if (fin == NULL)
    {
        perror("Could not open file\n");
        exit(EXIT_FAILURE);
    }
    
    // Establish variables for file I/O
    char line[32];
    char temp[32];
    char *token;
    int rows = 0;
    
    // Fill numberOfPuzzles from file
    fseek(fin, 0, SEEK_SET);
    rows = atof(fgets(line, 32, fin));
    
    currentHangmanGame->numberOfPuzzles = rows;
    
    // Allocate memory for 2D char array
    currentHangmanGame->puzzleWords = (char **) malloc (rows * sizeof(char *));
    for (int a = 0; a < rows; a++)
    {
        currentHangmanGame->puzzleWords[a] = (char *) malloc (32 * sizeof(char));
    }
    
    // Populate 2D char array
    for (int a = 0; a < rows; a++)
    {
        fgets(line, 31, fin);
        strcpy(temp, line);
        token = strtok(temp, "\n\r");
        strcpy(currentHangmanGame->puzzleWords[a], token);
        
    }
    
    
    // Close puzzleFile    
    fclose(fin);
}

bool isPuzzleOver(Hangman currentHangmanGame)
{
    if (currentHangmanGame->missedGuesses >= 7)
        return 1;
    else
        return 0;
}

bool isPuzzleSolved(Hangman currentHangmanGame)
{
    // Compare guessedWord and currentPuzzle
    if (strcmp(currentHangmanGame->guessedWord, currentHangmanGame->currentPuzzle) == 0)
        return 1;
    else
        return 0;
}

bool guessLetter(Hangman currentHangmanGame, char userChoice)
{
    bool letterInWord = 0;
    
    // Compare userChoice to currentHangmanGame->currentPuzzle
    
    for(int a = 0; a < strlen(currentHangmanGame->currentPuzzle); a++)
    {
        if (currentHangmanGame->currentPuzzle[a] == userChoice)
        {
            currentHangmanGame->guessedWord[a] = userChoice;
            letterInWord = 1;
        }
    }
    
    if(letterInWord == 1)
        return letterInWord;
    else
    {
        currentHangmanGame->missedGuesses++;
        return letterInWord;
    }
    
}

char* getGuessedWord(Hangman currentHangmanGame)
{
	// Returns a string with current state of guessed word (_ _ b _)

	return currentHangmanGame->guessedWord;
}

char* getStateOfHangman(Hangman currentHangmanGame)
{
    // Returns a string with current state of HANGMAN
    char *hangman = (char *) malloc(8 * sizeof(char));
    
    if (currentHangmanGame->missedGuesses == 0)
    {
        strcpy(hangman, "*******\n");
        return hangman;
    }
    else if (currentHangmanGame->missedGuesses == 1)
    {
        strcpy(hangman, "H******\n");
        return hangman;
    }
    else if (currentHangmanGame->missedGuesses == 2)
    {
        strcpy(hangman, "HA*****\n");
        return hangman;
    }
    else if (currentHangmanGame->missedGuesses == 3)
    {
        strcpy(hangman, "HAN****\n");
        return hangman;
    }
    else if (currentHangmanGame->missedGuesses == 4)
    {
        strcpy(hangman, "HANG***\n");
        return hangman;
    }
    else if (currentHangmanGame->missedGuesses == 5)
    {
        strcpy(hangman, "HANGM**\n");
        return hangman;
    }
    else if (currentHangmanGame->missedGuesses == 6)
    {
        strcpy(hangman, "HANGMA*\n");
        return hangman;
    }
    else if (currentHangmanGame->missedGuesses == 7)
    {
        strcpy(hangman, "HANGMAN\n");
        return hangman;
    }
    else
        return 0;
}

void freeHangmanGame(Hangman currentHangmanGame)
{
    // Free all allocated memory using free(array)
    free(currentHangmanGame->currentPuzzle);
    free(currentHangmanGame->guessedWord);
    free(currentHangmanGame->puzzleWords);
    for(int a =0; a < currentHangmanGame->numberOfPuzzles; a++)
    {
        free(currentHangmanGame->puzzleWords[a]);        
    }

}

char* displayCurrentPuzzle(Hangman currentHangmanGame)
{
    return currentHangmanGame->currentPuzzle;
}

char* displayGuessedWord(Hangman currentHangmanGame)
{
    return currentHangmanGame->guessedWord;
}