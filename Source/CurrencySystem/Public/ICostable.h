// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "ICostable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UICostable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CURRENCYSYSTEM_API IICostable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 GetCost();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TMap<FGameplayTag, int> GetCostBundle(); // a map of costs, and keys to be passed to the currency component
};
