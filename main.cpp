/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC patternm, and is responsable for all
user interaction. For game logic  see FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = FString;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
FBullCowGame BCGame; // instatiate a new game, which we re-use across plays

//The entry	
int main() {

	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();

	} while (bPlayAgain);
	return 0;
}
// plays a single game to complition
void PlayGame()
{
	BCGame.Reset();
	int32 maxTries = BCGame.GetMaxTries();
	FText Guess = "";

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while(!BCGame.isGameWon() && BCGame.GetCurrentTry() <= maxTries) {
		FText Guess = GetValidGuess();

		//Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n \n";
	}
	return;
	
}

void PrintIntro() {

	const int32 WORD_LENGHT = BCGame.GetHiddenWordLenght();
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;

	std::cout << "Can you guess the " << WORD_LENGHT;
	std::cout << " letter isogram I'm thinking of? \n";
	std::cout << std::endl;
	return;
}
void PrintGameSummary()
{
	if(BCGame.isGameWon())
	{
	
		std::cout << "Good job! YOU WON!! \n";
	}
	else
	{
		std::cout << "Better luck next time! \n";
	}

}

// loop continually unitl the user gives a valid guess
FText GetValidGuess	()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 currentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << currentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";

		std::getline(std::cin, Guess);

		Status = BCGame.checkGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << std::endl;
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " digit word. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << std::endl;
			std::cout << "Please enter all lower case letters. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << std::endl;
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		default:
			// assuming the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // Keep looping until we get no error / valid input
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again, with the same hidden word? (y/n)?";
	FText Responce = "";
	std::getline(std::cin, Responce);
	return(Responce[0] == 'y' || Responce[0] == 'Y');
	
}
