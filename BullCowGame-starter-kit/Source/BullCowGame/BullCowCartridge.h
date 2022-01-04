// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
		virtual void BeginPlay() override;
		virtual void OnInput(const FString& Input) override;
		void InitializeGame(const FString& Number);
		void EndGame();
	// Your declarations go below!
	private:
		bool AreDigitsDifferent(const FString& Number);
		bool CheckGuessedHiddenNumber(const FString& InputNumber);
		FString HiddenNumber;
		int8 Lives;
		bool bGameOver;
};
