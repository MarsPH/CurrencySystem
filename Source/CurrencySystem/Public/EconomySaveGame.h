// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "EconomySaveGame.generated.h"

/**
 * 
 */

USTRUCT()
struct FBankSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FGameplayTag, int32> CostBundle;

	UPROPERTY()
	bool isEmpty = false;
	
};
UCLASS()
class CURRENCYSYSTEM_API UEconomySaveGame : public USaveGame
{
	GENERATED_BODY()

	public:
	UPROPERTY()
	TMap<FGameplayTag, int32> PlayerCurrencyData;

	UPROPERTY()
	TMap<FName, FBankSaveData> BankData;
};
