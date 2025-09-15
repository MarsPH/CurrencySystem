// Fill out your copyright notice in the Description page of Project Settings.


#include "Costable.h"

#include "DiffUtils.h"
#include "Chaos/Deformable/ChaosDeformableCollisionsProxy.h"
#include "Components/BoxComponent.h"

// Sets default values
ACostable::ACostable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

int32 ACostable::GetCost_Implementation()
{
	return Cost;
}



// Called when the game starts or when spawned
void ACostable::BeginPlay()
{
	Super::BeginPlay();
}



// Called every frame
void ACostable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

