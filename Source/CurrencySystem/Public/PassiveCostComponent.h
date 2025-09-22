// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "PassiveCostComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURRENCYSYSTEM_API UPassiveCostComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPassiveCostComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, int> PassiveCostBundle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Interval;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
