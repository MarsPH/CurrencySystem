// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PassiveIncomeSource.h"
#include "Components/ActorComponent.h"
#include "PassiveCostComponent.generated.h"

class ACostable;
class UEconomyManagerComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURRENCYSYSTEM_API UPassiveCostComponent : public UActorComponent, public IPassiveIncomeSource
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPassiveCostComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, int> PassiveCostBundle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Interval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEconomyManagerComponent* EconomyManager;

	virtual TMap<FGameplayTag, int> GetIncomeBundles_Implementation() override;

	virtual float GetInterval_Implementation() override;

	virtual bool IsActive_Implementation() override;

	virtual EDepositType GetIncomeDepositState_Implementation() override;

	virtual void DepositIncomeIntoBank_Implementation(const TMap<FGameplayTag, int32>& IncomeBundle) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	EDepositType MyEnumValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACostable* Bank;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, int> IncomeBundleToStoreInBank;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
