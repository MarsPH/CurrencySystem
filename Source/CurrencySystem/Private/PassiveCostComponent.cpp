// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveCostComponent.h"

// Sets default values for this component's properties
UPassiveCostComponent::UPassiveCostComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


TMap<FGameplayTag, int> UPassiveCostComponent::GetIncomeBundles_Implementation()
{
	return PassiveCostBundle;
}

float UPassiveCostComponent::GetInterval_Implementation()
{
	return Interval;
}

bool UPassiveCostComponent::IsActive_Implementation()
{
	return true;
}

// Called when the game starts
void UPassiveCostComponent::BeginPlay()
{
	Super::BeginPlay();

	EconomyManager->RegisterSource(this); //it register itself for now in begin play with economy manager

	// ...
	
}


// Called every frame
void UPassiveCostComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

