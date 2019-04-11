/*
 * File Name: client.c
 * Author: Daryl Meade
 * Assignment: Project 1
 * Description: Client interface for Hangman
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "hangman.h"


int main()
{
    char filename[32], newFilename[32];
    char userChoice;
    int menuChoice;
    bool guess = 0;
    
    Hangman currentHangmanGame;

    printf("Welcome to Hangman!\n");
    printf("Please enter the name of the file containing your puzzles:\n");
    scanf("%s", filename);
    
    printf("\n");
    
    currentHangmanGame = createHangmanGame(filename);
    
    newHangmanPuzzle(currentHangmanGame);
    
	printf("Here's your puzzle!\n");
    printf("\n");
    
    while(menuChoice != 3)
    {
    
    while(isPuzzleOver(currentHangmanGame) != 1 && isPuzzleSolved(currentHangmanGame) != 1)
    {
        printf("Word: %s\n", displayGuessedWord(currentHangmanGame));
        printf("HANGMAN status: %s\n", getStateOfHangman(currentHangmanGame));
        printf("Please guess a letter: ");
        scanf(" %c", &userChoice);
        printf("\n");
    
        guess = guessLetter(currentHangmanGame, userChoice);
    
        if(guess == 0)
        {
            printf("Sorry, that letter isn't in the word.\n \n");
        }
        else
            printf("Great job!\n \n");
        
    }
    
    if(isPuzzleOver(currentHangmanGame) == 1)
    {
        printf("You lose!\n \n");
    }
    
    if(isPuzzleSolved(currentHangmanGame) == 1)
    {
        printf("You win!\n \n");
    }
    
    printf("Would you like to:\n");
    printf("\t1.  Play a new game\n");
    printf("\t2.  Load a new file of puzzles\n");
    printf("\t3.  Quit\n");
    scanf("%d", &menuChoice);
    
    switch(menuChoice)
    {
        case 1:
            newHangmanPuzzle(currentHangmanGame);
            break;
        case 2:
            printf("Please enter the new filename: ");
            scanf("%s", newFilename);
            loadPuzzleFile(currentHangmanGame, newFilename);
            newHangmanPuzzle(currentHangmanGame);
            break;
        case 3:
            freeHangmanGame(currentHangmanGame);
            break;
        default:
            printf("Please make a valid selection.\n");
        
    }
    
    }
    
    return 0;
}


