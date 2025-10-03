// Fill out your copyright notice in the Description page of Project Settings.
// =============================================================
// CurrencyComponent.cpp
//
// Handles all currency logic for an Actor:
//   • Stores balances per currency type
//   • Provides Add / Spend / Query API
//   • Supports purchase through ICostable interface
//   • Manages collision box for auto-purchase overlaps
//
// Organization of this file:
//   1. Constructor & Initialization
//   2. Unreal Lifecycle (BeginPlay, Tick)
//   3. Currency Management (Add, Spend, CanAfford)
//   4. Purchase Logic (using ICostable)
//   5. Collision Handling (Begin/End overlap)
//
// Notes:
//   - Debug output uses PrintString, standardized colors
//   - Tick can be disabled if not required
//   - BoxComponent is created at runtime and attached to Owner
// =============================================================

#include "CurrencyComponent.h"

#include "ICostable.h"
#include "MovieSceneTracksComponentTypes.h"
#include "PassiveCostComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/RepLayout.h"

// =============================================================
// Constructor & Initialization
// =============================================================

// Sets default values for this component's properties
UCurrencyComponent::UCurrencyComponent():MaxCurrency(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	// You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//A box component to be created, to manages the overlap
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent"));
	//setting the box extent bigger than the player for an easier feedback
	
	BoxComponent->SetBoxExtent(FVector(74.0f, 125.0f, 100.0f));
	//get the root component of the owner/ attaches the box to it

	//set relative location of the box to the component, so the half of the box is not in the ground
	BoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	
}

// Called when the game starts
void UCurrencyComponent::BeginPlay()
{
	Super::BeginPlay();

	//validates if owner exist, otherwise crash will happen
	if (AActor* Owner = GetOwner())
	{
		BoxComponent = NewObject<UBoxComponent>(Owner); //creates an object and assign to box component
		if (BoxComponent != nullptr){ //checks box component to be not null

			BoxComponent->RegisterComponent();
			//attach to the root so it won't just goof around in the spawning point
			BoxComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			//binds the begin overlap function with the overlap event, so when overlap happens the function fires
			BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UCurrencyComponent::OverlapBegin);
		}
	}

}

// =============================================================
// Currency Management
// =============================================================

void UCurrencyComponent::AddCurrency(int32 Amount, FGameplayTag CurrencyType)
{
	//adds the new amount to the current currency with its key, so that amount can be updated accordingly
	CurrencyBalances[CurrencyType] += Amount;

	// broadcasts current, so the ui can notice the currency change, and updates it
	OnCurrencyChanged.Broadcast(CurrencyBalances[CurrencyType], Amount,
		true, CurrencyType);
}

bool UCurrencyComponent::ApplyTransaction(TMap<FGameplayTag, int> CostBundle)
{
	//if current currency is less than 0 or the amount will cause current currency to be 0 return
	//Note that some items can be free and be purchased while CurrentCurrency = 0

	for (const TPair<FGameplayTag, int>& Entry : CostBundle)
	{
		FGameplayTag CurrencyType = Entry.Key;
		int32 CostAmount = Entry.Value;

		if (CurrencyBalances[CurrencyType] + CostAmount < 0) 
		{
			return false; //if the current amount held or be held will be less than 0, then won't let the spending happen
		}
	}

	for (const TPair<FGameplayTag, int>& Entry : CostBundle)
	{
		FGameplayTag CurrencyType = Entry.Key;
		int32 CostAmount = Entry.Value;

		CurrencyBalances[CurrencyType] += CostAmount;// reduces the currenct currency that is held, so spending happens
		OnCurrencyChanged.Broadcast(CurrencyBalances[CurrencyType], CostAmount, false,
			CurrencyType);// broadcasts current currency and deltaAmount, so UI can update
	}
	return true;
}

// =============================================================
// Purchase Logic
// =============================================================

void UCurrencyComponent::Purchase(UObject* ObjectToBuy)
{
	//checks that the ObjectToBuy implments Costable interface. 
	bool bIsImplemented = ObjectToBuy->GetClass()->ImplementsInterface(UICostable::StaticClass());
	if (!bIsImplemented)
	{
		return;// if no, it returns
	}
	else
	{
		int32 Cost = IICostable::Execute_GetCost(ObjectToBuy);// calls the function that is implemented in obj
		TMap<FGameplayTag, int> CostBundle = IICostable::Execute_GetCostBundle(ObjectToBuy);
		//FGameplayTag CurrencyCostType = IICostable::Execute_GetCostType(ObjectToBuy);
		if (Cost < 0)
			return;// if cost is less than 0, returns
		else
		{
			ApplyTransaction(CostBundle);// passes cost to the function of spendCurrnecy
		}
	}
}



// =============================================================
// Collision Handling
// =============================================================

//Overlap function to get a reference to an actor which demands/gives currency.
void UCurrencyComponent::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Checks for the implementation of the otherClass that is overlapped
	//if implmented, tries to assign the Cost of the costable to a variable
	//The variable passes to the SpendCurrency()

	//tries to get the passive cost component on the obj if not exist then proceeds with regular costable purchase
	bool isEmptiable = IICostable::Execute_IsEmptiable(OtherActor);
	if (isEmptiable)
	{
		//empty its bank(note that regular passive components that sends to currency component dont need to be overlapped)
		Purchase(OtherActor);
		IICostable::Execute_EmptyBank(OtherActor);

	}
	else
	{
		Purchase(OtherActor);
	}
}

/*	
		UKismetSystemLibrary::PrintString(this, stringResult, true, false,
			FColor::Red, 10, "SpentCurrency");
*/