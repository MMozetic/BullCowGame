// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    const FString NumbersListPath = FPaths::ProjectContentDir() / TEXT("NumbersList/Numbers.txt");
    FFileHelper::LoadFileToStringArray(Numbers, *NumbersListPath);

    InitializeGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        InitializeGame();
    }
    else
    {
        if (CheckGuessedHiddenNumber(PlayerInput))
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

void UBullCowCartridge::InitializeGame()
{
    ClearScreen();

    HiddenNumber = Numbers[FMath::RandRange(0, Numbers.Num()-1)];
    Lives = HiddenNumber.Len();
    bGameOver = false;

    // ****************************
    // Introductory messages
    // ****************************
    PrintLine(TEXT("Hello my friend! Welcome to Bull Cows."));
    PrintLine(TEXT("Guess the %i digit number with all different digits."), HiddenNumber.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and press ENTER to continue..."));

    PrintLine(TEXT("DEBUG: %s"), *HiddenNumber);
}

bool UBullCowCartridge::AreDigitsDifferent(const FString& Number) const
{
    // Loop through the Number and check if some digits are repeating itself.

    for (int32 Index = 0; Index < Number.Len()-1; ++Index)
    {
        for (int32 Index2 = Index + 1; Index2 < Number.Len(); ++Index2) {
            if (Number[Index] == Number[Index2])
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
    else if (GuessedNumber == HiddenNumber)
    {
        PrintLine(TEXT("You have guessed the Hidden Number. Congrats!"));
        ReturnStatus = true;
    }
    else if (!AreDigitsDifferent(GuessedNumber))
    {
        PrintLine(TEXT("Input Number has digits that are repeating."));
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

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("The hidden number was %s."), *HiddenNumber);
    PrintLine(TEXT("Press ENTER to play again."));
}
