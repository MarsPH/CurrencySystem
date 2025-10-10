// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../../../../../../Program Files/Epic Games/UE_5.6/Engine/Plugins/Editor/GameplayTagsEditor/Source/GameplayTagsEditor/Private/GameplayTagEditorUtilities.h"
#include "Components/ActorComponent.h"
//#include "GameplayTags.h"
//#include "GameplayTagContainer.h"
#include "CurrencyComponent.generated.h"

class UBoxComponent;



// =============================================================
// Delegate: FCurrencyChanged
//
// Broadcasts whenever a currency balance changes.
// Parameters:
//   • CurrentCurrency   – the new total after the change
//   • DeltaAmount       – how much was added or spent
//   • isPositiveAmount  – true if currency was gained, false if spent
//   • CurrencyType      – the type of currency affected
//
// Typical use cases:
//   • Updating UI displays
//   • Triggering gameplay reactions when currency changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FCurrencyChanged, float, CurrentCurrncy, float, DeltaAmount, bool,
	isPositiveAmount, FGameplayTag, CurrencyType);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrencyBalancesInitialized , TArray<FCurrencyEntry>, CurrencyEntries);

USTRUCT(BlueprintType)
struct FCurrencyEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Balance;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURRENCYSYSTEM_API UCurrencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// =============================================================
	// Constructor
	// =============================================================

	// Sets default values for this component's properties
	UCurrencyComponent();

	// =============================================================
	// Currency Data
	// =============================================================

	UPROPERTY(EditAnywhere)
	int32 MaxCurrency;

	// Array-based representation of balances (alternative to TMap)
	UPROPERTY(EditAnywhere)
	TArray<FCurrencyEntry> CurrencyBalancesArray;

	// Map-based representation of balances: CurrencyType → Amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, int32> CurrencyBalances;

	// =============================================================
	// Delegates & Events
	// =============================================================

	UPROPERTY(BlueprintAssignable)
	FCurrencyChanged OnCurrencyChanged;

	// Placeholder for array initialization event (not used yet)
	//UPROPERTY(BlueprintAssignable)
	//FOnCurrencyBalancesInitialized OnCurrencyBalancesInitialized;

	// =============================================================
	// Public API
	// =============================================================

	UFUNCTION(BlueprintCallable, Category="Currency|Management")
	void AddCurrency(int32 Amount, FGameplayTag CurrencyType);

	UFUNCTION(BlueprintCallable, Category="Currency|Management")
	bool ApplyTransaction(TMap<FGameplayTag, int32> CostBundle);

	// =============================================================
	// Collision
	// =============================================================

	UPROPERTY()
	UBoxComponent* BoxComponent;

	// =============================================================
	// Save & Load
	// =============================================================

	UFUNCTION(BlueprintCallable, Category="Currency|Getter & Setter")
	const TMap<FGameplayTag, int32> GetCurrencyBalances();

	UFUNCTION(BlueprintCallable, Category="Currency|Getter & Getter")
	void SetCurrencyBalances (TMap<FGameplayTag, int32> CurrencyBalanceBundles);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult); // overlapBegin
	
};
