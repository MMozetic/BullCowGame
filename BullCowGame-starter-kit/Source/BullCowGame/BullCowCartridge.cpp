// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitializeGame("1234");
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        InitializeGame("12345");
    }
    else
    {
        if (CheckGuessedHiddenNumber(Input))
        {
            PrintLine(TEXT("You win!"));
            EndGame();
        }
        else if (Lives)
        {
            PrintLine(TEXT("Try again... Remaining Lives: %i"), Lives);
        }
        else
        {
            PrintLine(TEXT("You lose!"));
            EndGame();
        }
    }
}

bool UBullCowCartridge::AreDigitsDifferent(const FString& Number)
{
    // Loop through the Number and check if some digits are repeating itself.

    for (int i = 0; i < Number.Len()-1; ++i)
    {
        for (int j = i + 1; j < Number.Len(); ++j) {
            if (Number[i] == Number[j])
            {
                return false;
            }
        }
    }

    return true;
}

bool UBullCowCartridge::CheckGuessedHiddenNumber(const FString& GuessedNumber)
{

    bool ReturnStatus = false;

    if (GuessedNumber.Len() != HiddenNumber.Len())
    {
        PrintLine(TEXT("Hidden Number is %i digits long, but %i are entered."), HiddenNumber.Len(), GuessedNumber.Len());
    }
    else if (!AreDigitsDifferent(GuessedNumber))
    {
        PrintLine(TEXT("Input Number has digits that are repeating."));
    }
    else if (GuessedNumber == HiddenNumber)
    {
        PrintLine(TEXT("You have guessed the Hidden Number. Congrats!"));
        ReturnStatus = true;
    }
    else if (GuessedNumber != HiddenNumber)
    {
        PrintLine(TEXT("Entered Number and Hidden Number are different."));
        --Lives;
    }
    else
    {
        PrintLine(TEXT("Undefined state"));
    }

    return ReturnStatus;
}

void UBullCowCartridge::InitializeGame(const FString& Number)
{
    ClearScreen();

    HiddenNumber = Number;
    Lives = HiddenNumber.Len();
    bGameOver = false;

    // ****************************
    // Introductory messages
    // ****************************
    PrintLine(TEXT("Hello my friend! Welcome to Bull Cows."));
    PrintLine(TEXT("Guess the %i digit number with all different digits."), HiddenNumber.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and press ENTER to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press ENTER to play again."));
}
