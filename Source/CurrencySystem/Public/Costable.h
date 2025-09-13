// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICostable.h"
#include "GameFramework/Actor.h"
#include "ICostable.h"

#include "Costable.generated.h"
class UBoxComponent;

UCLASS()
class CURRENCYSYSTEM_API ACostable : public AActor, public IICostable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACostable();
	virtual int32 GetCost_Implementation() override;; //overreding of the interface of ICOSTABLE
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
