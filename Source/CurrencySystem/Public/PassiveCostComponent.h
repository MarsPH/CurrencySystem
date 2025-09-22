// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EconomyManagerComponent.h"
#include "GameplayTagContainer.h"
#include "PassiveIncomeSource.h"
#include "Components/ActorComponent.h"
#include "PassiveCostComponent.generated.h"


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

	virtual TMap<FGameplayTag, int> GetIncomeBundles_Implementation __override();

	virtual float GetInterval_Implementation() __override;

	virtual bool IsActive_Implementation() __override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
