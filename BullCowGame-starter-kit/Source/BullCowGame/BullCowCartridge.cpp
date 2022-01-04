// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

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

bool UBullCowCartridge::GuessHiddenNumber(const FString& InputNumber)
{

    bool ReturnStatus = false;

    if (InputNumber.Len() != HiddenNumber.Len())
    {
        PrintLine(TEXT("Entered Number has different number of digits compared to Hidden Number."));
        --Lives;
    }
    else if (!AreDigitsDifferent(InputNumber))
    {
        PrintLine(TEXT("Input Number has digits that are repeating."));
        --Lives;
    }
    else if (InputNumber == HiddenNumber)
    {
        PrintLine(TEXT("You have guessed the Hidden Number. Congrats!"));
        ReturnStatus = true;
    }
    else if (InputNumber != HiddenNumber)
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
    // Set the new HiddenNumber and the number of Lives.
    HiddenNumber = Number;
    Lives = HiddenNumber.Len();
}

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitializeGame("1234");

    // ****************************
    // Introductory messages
    // ****************************
    PrintLine(TEXT("Hello my friend! Welcome to Bull Cows."));
    PrintLine(TEXT("Guess the " + FString::FromInt(HiddenNumber.Len()) + 
        " digit number with all different digits."));
    PrintLine(TEXT("Please press ENTER to continue..."));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    if (GuessHiddenNumber(Input))
    {
        PrintLine(TEXT("You win!"));
    }
    else
    {
        if (Lives)
        {
            PrintLine(TEXT("Try again..."));
            PrintLine(TEXT("Remaining Lives: " + FString::FromInt(Lives)));
        }
        else
        {
            PrintLine(TEXT("You lose!"));
        }
    }
}