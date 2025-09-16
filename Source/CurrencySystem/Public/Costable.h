// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ICostable.h"
#include "GameFramework/Actor.h"
#include "ICostable.h"
#include "ICostDisplayable.h"
#include "Components/WidgetComponent.h"

#include "Costable.generated.h"
class UBoxComponent;

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoxOverlappedWithPlayer, int32, Cost);

UCLASS()
class CURRENCYSYSTEM_API ACostable : public AActor, public IICostable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACostable();
	virtual int32 GetCost_Implementation() override; //overreding of the interface of ICOSTABLE

	virtual FGameplayTag GetCostType_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag CostCurrencyType;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult); // overlapBegin

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex); // OverlapEnd

	UFUNCTION()
	void OnWidgetReady();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* WidgetComponent;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
