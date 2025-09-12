// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrencyComponent.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UCurrencyComponent::UCurrencyComponent(): CurrentCurrency(0), MaxCurrency(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCurrencyComponent::AddCurrency(int32 Amount)
{
	CurrentCurrency += Amount; 

	TArray<int32> MyCurrencies = {1, 2, 3, 3, 3, 1};

	FString stringResult = TEXT("");
	for (int i = 0; i < MyCurrencies.Num(); i++)
	{
		stringResult = stringResult.Appendf(TEXT("Number_%d: %d, "), i + 1, MyCurrencies[i]);
	}
	
	UKismetSystemLibrary::PrintString(this, stringResult, true, false, FColor::Red, 10, "Currency");
}

bool UCurrencyComponent::SpendCurrency(int32 Amount)
{
	return true;
}

bool UCurrencyComponent::CanAfford(int32 Amount)
{
	return true;
}


// Called when the game starts
void UCurrencyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCurrencyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

