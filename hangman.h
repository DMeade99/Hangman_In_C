/*
 * File Name: hangman.h
 * Author: Daryl Meade
 * Assignment: Project 1
 * Description: Function declarations for hangman game
 */

#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdbool.h>

typedef struct hangman *Hangman;

Hangman createHangmanGame(char *puzzleFile);

void newHangmanPuzzle(Hangman currentHangmanGame);

void loadPuzzleFile(Hangman currentHangmanGame, char *puzzleFile);

bool isPuzzleOver(Hangman currentHangmanGame);

bool isPuzzleSolved(Hangman currentHangmanGame);

bool guessLetter(Hangman currentHangmanGame, char userChoice);

char* getGuessedWord(Hangman currentHangmanGame);

char* getStateOfHangman(Hangman currentHangmanGame);

void freeHangmanGame(Hangman currentHangmanGame);

char* displayCurrentPuzzle(Hangman currentHangmanGame);

char* displayGuessedWord(Hangman currentHangmanGame);


#endif
