#include "FBullCowGame.h"
#include <map>
#define TMap std::map


bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}
FBullCowGame::FBullCowGame()
{
	Reset();
}

FBullCowGame::~FBullCowGame()
{
}

void FBullCowGame::Reset()
{
	
	const FString HIDDEN_WORD = "pla"; //this MUST be an isogram
	bGameIsWon = false;
	MyCurrentTry = 1;	
	MyHiddenWord = HIDDEN_WORD;
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,16},{7,20} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return 	MyHiddenWord.length();
}


EGuessStatus FBullCowGame::CheckGeussValidity(FString Guess) const
{
	if (!IsIsogram(Guess))	//if the geuss isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowcase(Guess))// if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length()!=GetHiddenWordLength())// if the guess length is wrong then 
	{
		return EGuessStatus::Wrong_Length;

	}
	else
	{
		return EGuessStatus::Ok;
	}
	
}

//recieve a VALiD guess , incriments turn and return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	// incriment the turn number
	MyCurrentTry++;
	FBullCowCount BullCOwCount;
	// loop through all letters in the guess
	int32 WordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{

		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{


			// compare letters against the hidden word
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{

				if (MHWChar == GChar)
				{
					BullCOwCount.Bulls++; //incriment bulls
				}
				else 
				{
					BullCOwCount.Cows++;//must be the cow
				}
				
			}

		}
	}
	if (BullCOwCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCOwCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 nad 1 letter words asisograms
	if (Word.length() <= 1) {
		return true;
	}
	TMap<char, bool> LetterSeen; //setup the map
	for (auto Letter : Word)	// for all letter of the word 
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowcase(FString Word) const
{
	for (auto Letter : Word)
	{
		// if not a lowercase letter then return false
		if (islower(Letter))
		{
			return true;
		}
	}
	return false;
}


