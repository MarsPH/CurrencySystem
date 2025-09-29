// Fill out your copyright notice in the Description page of Project Settings.


#include "EconomyManagerComponent.h"

#include "CurrencyComponent.h"
#include "FunctionalUIScreenshotTest.h"
#include "PassiveIncomeSource.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

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
	for (auto& Source : PassiveSources)
	{
		if (!Source) continue;  
		// Skip if the source pointer is invalid

		ElapsedTimeMap[Source] += GlobalInterval;  
		// Add the manager’s tick interval to this source’s elapsed time counter

		if (!Source->IsActive()) continue;  
		// Skip if the source is currently inactive (e.g. disabled building)

		if (ElapsedTimeMap[Source] >= Source->GetInterval())
		{
			auto Bundle = Source->GetIncomeBundles();  
			// Get the map of resources (Tag → Amount) from the source

			if (CurrencyComponent)
			{
				CurrencyComponent->ApplyTransaction(Bundle);  
				// Apply the entire resource bundle to the player’s wallet
			}

			ElapsedTimeMap[Source] = 0.0f;  
			// Reset this source’s elapsed timer so it can count again
		}
	}
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

	//temperoray assigment 
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0); // get the player

	if (Player)
	{
		CurrencyComponent = Player->FindComponentByClass<UCurrencyComponent>(); // assign the currency comp of the player
		// to this reference
	}
	
	// ...
	
}


// Called every frame
void UEconomyManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

