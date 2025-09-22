// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "PassiveIncomeSource.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPassiveIncomeSource : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CURRENCYSYSTEM_API IPassiveIncomeSource
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TMap<FGameplayTag, int32> GetIncomeBundles() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	float GetInterval() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsActive() const;
};
