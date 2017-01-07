//
//  main.cpp
//  BullCowGame
//
//  Created by Slyta Sound on 12/5/16.
//  Copyright © 2016 Slyta Sound. All rights reserved.
////
//
//
/* This is the console excecutable, that makes use of the BullCow class
 This acts as the view in a MVC pattern, and is responsible for all user interaction. For game logic see the FBullCowGame class.
 */

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"
//#include <random>

//making syntax match unreal
using FText = std::string;
using int32 = int;


FBbullCowGame BCGame;  //Giving global access to the BCGame
////

////
//Function declarations (defined after return 0) not in a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

////

////
//Begin prog
int main()
{
    do
    {
        PrintIntro();
        PlayGame();
        
    }
    while(AskToPlayAgain());
    
    std::cout << std::endl;
    return 0;
}
//End prog
////

////
//Definitions
void PrintIntro()           // introduce the game
{
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout << "        <=}---{=>      <---> " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |----- |              |---,,-|  * " <<std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    BCGame.BullCowHint();
    std::cout << std::endl;
    return;
}

void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    std::cout<< "You have " << MaxTries << " tries to guess the right word!\n" << std::endl;
    
    //loop asking for guesses, while the game is NOT won and there are still guesses remaining.
    while (!BCGame.bIsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        
            FText Guess = GetValidGuess();
            
            //submit a valid guess to the game, and receive counts
            FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
            
            std::cout << "Your guess was " << Guess << ".\n";
            std::cout << "Bulls = " << BullCowCount.Bulls << ". ";
            std::cout << "Cows = " << BullCowCount.Cows << ".\n";
        if (!BCGame.bIsGameWon()) {
            std::cout << "You have " << (BCGame.GetMaxTries()+1) - BCGame.GetCurrentTry() << " guesses left.\n\n"; }
        else {std::cout <<"\n\n";}
    }
        
}
                                                                              //loop until player gives a valid guess
FText GetValidGuess()
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do {                                                                      // get a guess from the player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << ". Enter your guess now: ";
        std::getline(std::cin,Guess);
    
        Status = BCGame.CheckGuessValidity(Guess);
        
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std:: cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std:: cout << "Please use only lowercase letters while guessing.\n";
                break;
            case EGuessStatus::Not_Isogram:
                std:: cout << "An isogram is a word in which each letter is used only once.\nPlease enter an isogram.\n";
                break;
            default:
                break;
        }
        std:: cout << std::endl;
    
    } while (Status != EGuessStatus::OK);
    return Guess;
}

bool AskToPlayAgain()
{
    BCGame.IncrementPlayThroughCounter();//increment PlayThroughCounter
    BCGame.PrintGameSummary();
    std::cout << "\nDo you want to play again, with the same word? (y/n)";
    FText Response = "";
    getline(std::cin,Response);
    
    return (Response[0] == 'y' || Response[0] =='Y');
}
////
