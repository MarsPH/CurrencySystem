// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrencyComponent.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UCurrencyComponent::UCurrencyComponent(): CurrentCurrency(0), MaxCurrency(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	// You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCurrencyComponent::AddCurrency(int32 Amount)
{
	CurrentCurrency += Amount;//											adds the new amount to the current currency
	FString stringResult = TEXT("");

	stringResult = stringResult.Appendf(TEXT("Current Currency: %d") ,CurrentCurrency);
	
	UKismetSystemLibrary::PrintString(this, stringResult, true, false,
		FColor::Red, 10, "AddedCurrency");//									prints the result to the screen

	

	//TArray<int32> MyCurrencies = {1, 2, 3, 3, 3, 1}; EDU: a way to write array
/*
	FString stringResult = TEXT("")
	for (int i = 0; i < MyCurrencies.Num(); i++)
	{
		stringResult = stringResult.Appendf(TEXT("Number_%d: %d, "), i + 1, MyCurrencies[i]);
	}
	
	UKismetSystemLibrary::PrintString(this, stringResult, true, false, FColor::Red, 10, "Currency");
*/	
}

bool UCurrencyComponent::SpendCurrency(int32 Amount)
{
	if (CurrentCurrency <= 0)
	{
		return false;
	}
	else
	{
		CurrentCurrency -= Amount;// reduces the currenct currency that is held

		FString stringResult = TEXT(""); //assigns text that shows current currency to var

		stringResult = stringResult.Appendf(TEXT("Current Currency: %d") ,CurrentCurrency);// appends resultString
		
		UKismetSystemLibrary::PrintString(this, stringResult, true, false,
			FColor::Red, 10, "SpentCurrency");
		return true;
	}
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

