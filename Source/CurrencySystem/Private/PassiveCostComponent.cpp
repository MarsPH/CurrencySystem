// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveCostComponent.h"

#include "AsyncTreeDifferences.h"
#include "Costable.h"
#include "EconomyManagerComponent.h"
#include "ICostable.h"

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
	UE_LOG(LogTemp, Warning, TEXT("[%s] PassiveCostBundle.Num() = %d"),
	       *GetOwner()->GetName(),
	       PassiveCostBundle.Num());

	for (const auto& Elem : PassiveCostBundle)
	{
		UE_LOG(LogTemp, Warning, TEXT("   Tag: %s  Amount: %d"),
		       *Elem.Key.ToString(), Elem.Value);
	}

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

EDepositType UPassiveCostComponent::GetIncomeDepositState_Implementation()
{
	return DepositType;
}

void UPassiveCostComponent::DepositIncomeIntoBank_Implementation(const TMap<FGameplayTag, int32>& IncomeBundle)
{
	//in order to know if bank is emptied already or not
	//TMap<FGameplayTag, int32> BankBundle = IICostable::Execute_GetCostBundle(Bank); //to store the bank bundle
	if (Bank == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Bank is null"));
		return;
	}
	
	
	if (IICostable::Execute_GetIsEmpty(Bank))
	{
		//SetsIncome Bundle to 0 if BankBundle is 0 to not pass a value again and then sets BundleToStoreEmptied to true
		for (auto& Elem : IncomeBundleToStoreInBank)
		{
			Elem.Value = 0;
		}
		IICostable::Execute_SetIsEmpty(Bank, false);
	}
	else
	{
		//Depositing Value
		for (auto& ElemToAdd : IncomeBundle)
		{
			IncomeBundleToStoreInBank.FindOrAdd(ElemToAdd.Key) += ElemToAdd.Value;
		}
		
		IICostable::Execute_SetCostBundle(Bank->_getUObject(), IncomeBundleToStoreInBank);
	}
}

void UPassiveCostComponent::EmptyBank_Implementation()
{
	//SetsIncome Bundle to 0 if BankBundle is 0 to not pass a value again and then sets BundleToStoreEmptied to true
	for (auto& Elem : IncomeBundleToStoreInBank)
	{
		IncomeBundleToStoreInBank.FindOrAdd(Elem.Key) = 0;
	}
}


// Called when the game starts
void UPassiveCostComponent::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			if (UEconomyManagerComponent* Manager = Pawn->FindComponentByClass<UEconomyManagerComponent>())
			{
				Manager->RegisterSource(this);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("No EconomyManagerComponent found on Player Pawn!"));
			}
		}
	}

	// ...
}


// Called every frame
void UPassiveCostComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
