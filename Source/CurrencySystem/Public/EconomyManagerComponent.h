// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurrencyComponent.h"
#include "Components/ActorComponent.h"
#include "PassiveIncomeSource.h"
#include "EconomyManagerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CURRENCYSYSTEM_API UEconomyManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEconomyManagerComponent();

	// All registered passive income sources (via interface)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TScriptInterface<IPassiveIncomeSource>> PassiveSources;

	// Timer handle for the economy tick
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle EconomyTickTimer;

	// Map of elapsed time per source
	TMap<TScriptInterface<IPassiveIncomeSource>, float> ElapsedTimeMap;

	// Global tick interval (seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GlobalInterval = 1.0f;

	// Reference to the player’s currency component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurrencyComponent* CurrencyComponent;

	// Register a passive source (must implement interface)
	UFUNCTION(BlueprintCallable)
	void RegisterSource(class UPassiveCostComponent* Source);

	// Economy tick
	UFUNCTION(BlueprintCallable)
	void TickEconomy();

	//Saving & Loading
	UFUNCTION(BlueprintCallable)
	void SaveEconomy();

	UFUNCTION(BlueprintCallable)
	void LoadEconomy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override; 
};
