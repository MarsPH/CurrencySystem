// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CurrencyComponent.h"
#include "PassiveCostComponent.h"
#include "Components/ActorComponent.h"
#include "EconomyManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURRENCYSYSTEM_API UEconomyManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEconomyManagerComponent();
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	TArray<UPassiveCostComponent*> PassiveSources; //to store the passive soruces

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle EconomyTickTimer;// how often the passive tick should be done
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GlobalInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurrencyComponent* CurrencyComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
