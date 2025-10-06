#include "CostableRestorer.h"
#include "Components/BoxComponent.h"
#include "Costable.h"
#include "TimerManager.h"

ACostableRestorer::ACostableRestorer()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetBoxExtent(FVector(100.f));
}

void ACostableRestorer::BeginPlay()
{
	Super::BeginPlay();

	if (bRestoreOnOverlap)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACostableRestorer::OnOverlapBegin);
	}
}

void ACostableRestorer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
									   const FHitResult& SweepResult)
{
	if (!bRestoreOnOverlap) return;

	if (RestoreDelay > 0.f)
	{
		GetWorldTimerManager().SetTimerForNextTick([this]() { RestoreAll(); });
	}
	else
	{
		RestoreAll();
	}
}

void ACostableRestorer::RestoreAll()
{
	for (ACostable* Costable : TargetCostables)
	{
		if (IsValid(Costable))
		{
			Costable->Restore();
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Restorer %s restored %d Costables"), *GetName(), TargetCostables.Num());
}
