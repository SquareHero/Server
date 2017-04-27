/* This is console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//To make syntax Unreal friendly
using FText = std::string;
using int32 = int;


//function prototype as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
FBullCowGame BCGame;


int main()
{

	
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain= AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}


//introduce the game
void PrintIntro() {

	
	std::cout << "Welcome to Bull and Cows , a fun word game" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of? \n";
	std::cout << std::endl;

	return;

}

//plys a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//look asking for guess while the game is not won
	//and there are still tries remain
	//loop for the number of turns asking for guess
	
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); 

		//Submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

	
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ".Cows= = " << BullCowCount.Cows<<"\n\n";

		
	}
	PrintGameSummary();
	
}

//get a guess from player
FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::InvalidStatus;
	FText Guess = "";
	do {
		int32 MyCurrentTry = BCGame.GetCurrentTry();
		
	
		std::cout << "Try " << MyCurrentTry << " of "<<BCGame.GetMaxTries()<<". Enter your guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGeussValidity(Guess);
		switch (Status)
		{

		case EGuessStatus::Not_Isogram:
			std::cout << "Please Enter a word without repeat letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			break;

		}
		
	} while (Status != EGuessStatus::Ok); // keep looping utill  we get no errors
	return Guess;
	
}

bool AskToPlayAgain()
{
	
	std::cout << " Do you want to play again?(y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
