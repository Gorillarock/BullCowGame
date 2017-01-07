//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Slyta Sound on 12/7/16.
//  Copyright © 2016 Slyta Sound. All rights reserved.
//
/*
 The game logic (no view code or direct user interaction)
 The game is a simple guess the word game based on Mastermind
 */

#pragma once
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

//formating for unreal standars
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
    int32 GetPlayThroughCounter() const;
    
    ////
    
    ////
    //Semi-Getters
    EGuessStatus CheckGuessValidity(FString Guess) const;
    EGameSummary CheckGameSummary() const;
    void IncrementPlayThroughCounter();
    ////
    
    //user recieved value for desired word length
   // int32 VariableHWLin;
  
    
    
    void Reset();                           
    FBullCowCount SubmitValidGuess(FString);
    void PrintGameSummary();
    char TradeTurnForLetter();                                 //type of hint
    void quit();                                               //TODO make a more rich return value.
    void BullCowHint();                                        //reads out purpose of Bulls and Cows

// see constructor for initial values
private:
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    bool bIsIsogram(FString) const;
    bool bIsLowercase(FString) const;
    int32 PlayThroughCounter = 1;                                  //stores number of times played through
};
