/* The game logic (no view code or direct user interaction)
The game is a simple guess the word based on Mastermind
*/
#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{

	int32 Bulls = 0;
	int32 Cows = 0;

};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase

};

class FBullCowGame
{
public:
	FBullCowGame(); //Constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;

	bool isGameWon() const;
	EGuessStatus checkGuessValidity(FString) const;
	void Reset();
	FBullCowCount SubmitValidGuess(FString Guess);

private:
	int32 MyCurrentTry;
	int32 WordLenght;
	FString MyHiddenWord;
	bool bIsGameWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;

};