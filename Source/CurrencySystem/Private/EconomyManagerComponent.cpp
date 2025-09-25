// Fill out your copyright notice in the Description page of Project Settings.


#include "EconomyManagerComponent.h"

// Sets default values for this component's properties
UEconomyManagerComponent::UEconomyManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UEconomyManagerComponent::RegisterSource(TScriptInterface<IPassiveIncomeSource> Source)
{
	PassiveSources.Add(Source);
}

void UEconomyManagerComponent::TickEconomy()
{
	
}

// Called when the game starts
void UEconomyManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(
	EconomyTickTimer,  // the handle
	this, // object that owns the function
	&UEconomyManagerComponent::TickEconomy, // function pointer
	GlobalInterval, // time in seconds
	true // looping?
	);
	// ...
	
}


// Called every frame
void UEconomyManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

