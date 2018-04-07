#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();

}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5,10}, {6,15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLenght() const
{
	const int32 WORD_LENGHT = MyHiddenWord.length();
	return WORD_LENGHT;
}

bool FBullCowGame::isGameWon() const
{
	return bIsGameWon;
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;

	const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))// if the guess isn't an isogram 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) // if the guess isn't all lower case
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLenght()) // if the guess length is wrong 
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise
	{
		return EGuessStatus::OK;
	}

}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
				
					BullCowCount.Cows++;
				
				}
			}

		}
	}
	
	if (BullCowCount.Bulls == WordLength) 
	{

		bIsGameWon = true;

	}
	else 
	{
	
		bIsGameWon = false;

	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) {
	
		return true;
	
	}

	TMap<char, bool> LetterSeen;// setup our map
	for (char Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {//if the letter is in the map
			return false; // we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true;//add the letter to the map as seen.
		}
			
				
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) // for each letter in the word
	{
		if (islower(Letter)) { // if the letter is lower
			return true;
		}
		else { //otherwise
			return false;
		}
	}
	return true; // considering guesses like /0 are lowercase
}
