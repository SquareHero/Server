/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/
#pragma once
#include <string>
#include<iostream>

// to make syntax friendly
using FString = std::string;
using int32 = int;



struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows=0;
};
enum class EGuessStatus
{
	InvalidStatus,
	Ok,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase

};
enum class EResetStatus
{
	NO_Hidden_Word,
	OK
};

class FBullCowGame
{
public:

	FBullCowGame(); // constructor
	~FBullCowGame(); // deconstructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGeussValidity(FString) const;

	void Reset(); 
	//count Bulls&cows, and increase try # assuming valid guess.
	FBullCowCount SubmitValidGuess(FString);
	
	//Please try and ignore this and focus on the int32erface above
private:

	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsIsogram(FString) const;
	bool IsLowcase(FString) const;

};