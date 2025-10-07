// Fill out your copyright notice in the Description page of Project Settings.


#include "PassiveIncomeRegistrer.h"
#include "Costable.h"

#include "Components/BoxComponent.h"
// Sets default values
APassiveIncomeRegistrer::APassiveIncomeRegistrer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetBoxExtent(FVector(100.f));
}

// Called when the game starts or when spawned
void APassiveIncomeRegistrer::BeginPlay()
{
	Super::BeginPlay();

	if(RegisterOnOverlap)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APassiveIncomeRegistrer::OnOverlapBegin);
	}
}

// Called every frame
void APassiveIncomeRegistrer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APassiveIncomeRegistrer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!RegisterOnOverlap) return;

	// Prevent rapid re-triggering
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastToggleTime < 0.5f) // half-second buffer
		return;
	LastToggleTime = CurrentTime;

	if (IsRegistered)
	{
		Unregister();
		IsRegistered = false;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Unregistered."));
	}
	else
	{
		Register();
		IsRegistered = true;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Registered."));
	}
}

void APassiveIncomeRegistrer::Register()
{
	for(ACostable* Costable : PassiveSourcesToRegister)
	{
		if (!Costable)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Skipped: null Costable reference."));
			continue;
		}

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("Checking actor: %s"), *Costable->GetName()));

		// Find the component that implements the interface
		UActorComponent* Comp = Costable->FindComponentByInterface(UPassiveIncomeSource::StaticClass());
		if (Comp)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Found component: %s on %s"), *Comp->GetName(), *Costable->GetName()));

			IPassiveIncomeSource::Execute_RegisterIncomeSource(Comp);

			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Registered income source on: %s"), *Costable->GetName()));
		}
		else
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("No PassiveIncomeSource found on: %s"), *Costable->GetName()));
		}
	}
}

void APassiveIncomeRegistrer::Unregister()
{
	for (ACostable* Costable : PassiveSourcesToRegister)
	{
		if (!Costable)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Skipped: null Costable reference."));
			continue;
		}

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("Checking actor: %s"), *Costable->GetName()));

		// Find the component that implements the interface
		UActorComponent* Comp = Costable->FindComponentByInterface(UPassiveIncomeSource::StaticClass());
		if (Comp)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Found component: %s on %s"), *Comp->GetName(), *Costable->GetName()));

			IPassiveIncomeSource::Execute_UnregisterIncomeSource(Comp);

			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Unregistered on: %s"), *Costable->GetName()));
		}
		else
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("No PassiveIncomeSource found on: %s"), *Costable->GetName()));
		}
	}

}

