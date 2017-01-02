//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Slyta Sound on 12/7/16.
//  Copyright © 2016 Slyta Sound. All rights reserved.
//

#pragma once
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

using FString = std::string;
using int32 = int;
#endif /* FBullCowGame_hpp */

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};
enum class EGameSummary
{
    Won,
    Lost,
    invalid,
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase,
};

class FBbullCowGame
{
public:

    //Constructor
    FBbullCowGame();
    
    ////
    //Getters
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    FString GetHiddenWord() const;
    bool bIsGameWon() const;
    ////
    
    ////
    //Semi-Getters
    EGuessStatus CheckGuessValidity(FString Guess) const;
    EGameSummary CheckGameSummary() const;
    ////
    
    void Reset();                                              //TODO make a more rich return value.
    FBullCowCount SubmitValidGuess(FString);
    void PrintGameSummary();
    char TradeTurnForLetter();                                 //type of hint
    void quit();                                               //TODO make a more rich return value.



private:
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
    bool bGameIsWon;
    bool bIsIsogram(FString) const;
};
