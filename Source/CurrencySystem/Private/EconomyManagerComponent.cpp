#include "EconomyManagerComponent.h"

#include "CurrencyComponent.h"
#include "PassiveCostComponent.h"
#include "PassiveIncomeSource.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEconomyManagerComponent::UEconomyManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEconomyManagerComponent::RegisterSource(UPassiveCostComponent* Source)
{
	if (!Source)
	{
		UE_LOG(LogTemp, Error, TEXT("Tried to register null source in %s"), *GetOwner()->GetName());
		return;
	}

	if (Source->GetClass()->ImplementsInterface(UPassiveIncomeSource::StaticClass()))
	{
		TScriptInterface<IPassiveIncomeSource> InterfaceWrapper;
		InterfaceWrapper.SetObject(Source);                                   // the UObject*
		InterfaceWrapper.SetInterface(Cast<IPassiveIncomeSource>(Source));    // the interface pointer

		PassiveSources.Add(InterfaceWrapper);

		UE_LOG(LogTemp, Display, TEXT("Registered PassiveIncomeSource: %s"), *Source->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Component %s does not implement PassiveIncomeSource"),
			*Source->GetName());
	}
}

void UEconomyManagerComponent::TickEconomy()
{
	for (auto& Source : PassiveSources)
	{
		if (!Source) continue;

		UObject* SourceObject = Source.GetObject();
		if (!SourceObject) continue;

		// Validate interface
		if (SourceObject->GetClass()->ImplementsInterface(UPassiveIncomeSource::StaticClass()))
		{
			// IsActive
			if (!IPassiveIncomeSource::Execute_IsActive(SourceObject))
			{
				continue;
			}

			// Track elapsed time
			float& Elapsed = ElapsedTimeMap.FindOrAdd(Source);
			Elapsed += GlobalInterval;

			// Check interval
			const float Interval = IPassiveIncomeSource::Execute_GetInterval(SourceObject);
			if (Elapsed >= Interval)
			{
				// Get bundle
				const TMap<FGameplayTag, int32> Bundle = IPassiveIncomeSource::Execute_GetIncomeBundles(SourceObject);

				if (CurrencyComponent)
				{
					CurrencyComponent->ApplyTransaction(Bundle);
				}

				Elapsed = 0.0f; // reset timer
			}
		}
	}
}

void UEconomyManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Start the timer
	GetWorld()->GetTimerManager().SetTimer(
		EconomyTickTimer,
		this,
		&UEconomyManagerComponent::TickEconomy,
		GlobalInterval,
		true
	);

	if (GetWorld()->GetTimerManager().IsTimerActive(EconomyTickTimer))
	{
		UE_LOG(LogTemp, Warning, TEXT("Economy timer is ACTIVE"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Economy timer FAILED to start"));
	}

	// Temporary assignment of player's currency component
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player)
	{
		CurrencyComponent = Player->FindComponentByClass<UCurrencyComponent>();
	}
}

void UEconomyManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
