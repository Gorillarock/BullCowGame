//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Slyta Sound on 12/7/16.
//  Copyright © 2016 Slyta Sound. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <string>
#include <iostream>
#include <map>
#define TMap std::map

//#include <random>
using int32 = int;

//Constructor
FBbullCowGame::FBbullCowGame() { Reset(); }



////
//Getters
int32 FBbullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBbullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBbullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FBbullCowGame::GetHiddenWord() const { return MyHiddenWord; }
bool FBbullCowGame::bIsGameWon() const { return bGameIsWon; }
int32 FBbullCowGame::GetPlayThroughCounter() const { return PlayThroughCounter; }
////

////
//Semi Getters
EGuessStatus FBbullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!bIsIsogram(Guess))                                             //if the guess isn't an isogram
    { return EGuessStatus::Not_Isogram; }
    else if (!bIsLowercase(Guess))                                                                             //if the guess isn't all lowercase
    { return EGuessStatus::Not_Lowercase; }                             // function to check if all lowercase
    else if (Guess.length() != GetHiddenWordLength()) { return EGuessStatus::Wrong_Length; }    //if guess length is wrong
    else { return EGuessStatus::OK; }                                                           //otherwise
}
EGameSummary FBbullCowGame::CheckGameSummary() const        //Sets a status to be input to trigger function PrintGameSummary
{
    if (bGameIsWon == true) { return EGameSummary::Won; }
    else { return EGameSummary::Lost; }
}
void FBbullCowGame::IncrementPlayThroughCounter() {PlayThroughCounter++;}
////

void FBbullCowGame::Reset()
{
    constexpr int32 MAX_TRIES = 8;
    const FString HIDDEN_WORD = "donkey";
    MyCurrentTry = 1;
    MyMaxTries = MAX_TRIES;
    MyHiddenWord = HIDDEN_WORD;
    bGameIsWon = false;
}

// recieves a VALID Guess, increments turn, and returns out
FBullCowCount FBbullCowGame::SubmitValidGuess(FString Guess) {
    MyCurrentTry++;
    FBullCowCount BullCowCount;                                          // setup a return variable
    int32 WordLength = MyHiddenWord.length();                            //assuming same length as guess (because it is a valid guess)

    //loop through all letters in the hidden word
        for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {       //compare letter against the guess
            for (int32 GChar = 0; GChar < WordLength; GChar++) {         //if they match then
                if (Guess[GChar] == MyHiddenWord[MHWChar]) {             //if they're in the same place
                    if (MHWChar == GChar) { BullCowCount.Bulls ++; }
                    else { BullCowCount.Cows ++; }
            }
        }
    }
    
    if (BullCowCount.Bulls == WordLength) { bGameIsWon = true; }
    else { bGameIsWon = false; }
    return BullCowCount;
};

void FBbullCowGame::PrintGameSummary()
{
    FString TryOrTries = "tries";
    if (GetCurrentTry() == 2) { TryOrTries = "try"; }
    EGameSummary Summary = EGameSummary::invalid;
    Summary = FBbullCowGame::CheckGameSummary();
    switch (Summary) {
        case EGameSummary::Won :
            std::cout << "You won the game!\nIt took you " << GetCurrentTry() - 1 << " " << TryOrTries << " to guess the right word!\n";
            break;
        case EGameSummary::Lost :
            std::cout << "You lost the game.\nBetter luck next time.\n";
            break;
        default:
            std::cout << "Don't quit yet...\n";
            break;
    }
}

void FBbullCowGame::quit() // TODO give an actual function definition.
    {}

void FBbullCowGame::BullCowHint()
{
    if (GetPlayThroughCounter() == 1) {
    std::cout << "(A Bull means that one of your letters is in the correct spot.\n";
    std::cout << "A Cow means that one of your letters is present, just not in the right position.)\n";
    }
}

////Private Functions
bool FBbullCowGame::bIsIsogram(FString Word) const     //Isogram test using TMap
{
    //treat 0 and 1 letter words as isograms
    if (Word.length()<=1) { return true; }
    //set up a Map
    TMap<char, bool> LetterSeen;                 //declared TMap
    //loop through all the letters of the word
    for (auto Letter : Word)        // for all letters of the Word
    {
        Letter = tolower(Letter);       //handle mixed case
        
        //if letter is in the map
        if (LetterSeen[Letter] == true) { return false; }
            //we do not have an isogram
        else//otherwise
        {LetterSeen[Letter] = true;}    //add the letter to the map as seen
    }
    return true; //for example in cases where /0 is entered
}

bool FBbullCowGame::bIsLowercase(FString Word) const          //  lowercase checking function
{
    //need a range-based for loop, using auto, that spans the word (see bIsIsogram definition)
    for (auto Letter : Word)         //for each letter in the word
    {
        if (islower(Letter)) { return true; }
        else { return false; }
    }

    
    
    return true;
}


//Trial stuff

/*char FBbullCowGame::TradeTurnForLetter()
 {
 MyCurrentTry++; //Add 1 try to the MyCurrentTries count.
 //Present the player with a letter as well as the letter's position in the word.
 std::srand(std::time(0)); //seed random number generator
 int32 RandomNumber = std::rand()%(GetHiddenWordLength()+1);
 //create a variable to hold the value of the letter in the HiddenWord String.
 char Hint = MyHiddenWord[RandomNumber];
 return Hint;
 
 return 0
 }*/
