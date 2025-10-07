// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ICostable.h"
#include "GameFramework/Actor.h"
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

	virtual TMap<FGameplayTag, int32> GetCostBundle_Implementation() override;// to return the cost bundle in the interface

	virtual void SetCostBundle_Implementation( const TMap<FGameplayTag, int32>& bundle) override;

	virtual void EmptyBank_Implementation() override;

	virtual bool IsEmptiable_Implementation() override;

	virtual bool GetIsEmpty_Implementation() override;

	virtual void SetIsEmpty_Implementation(bool isEmptyInput) override;

	UFUNCTION()
	void UpdateWidget();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<FGameplayTag, int32> CostBundle;// instead of a single cost there is a cost bundle map now
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Cost;// this is not used anymore, other than the UI TBD

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag CostCurrencyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isEmptiable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isEmpty;

	UPROPERTY(BlueprintReadWrite)
	bool NeedWidgetUpdate;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Bank")
	FName BankID;

	UFUNCTION()
	TMap<FGameplayTag, int32> GetBankBundles();

	UFUNCTION()
	void SetBankBundle(const TMap<FGameplayTag, int32>& Newbundle);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Costable|Behvaior")
	bool IsVanishable = false;

	UFUNCTION(BlueprintCallable, Category="Costable|Behvaior")
	void Vanish();

	UFUNCTION(BlueprintCallable, Category="Costable|Behavior")
	void Restore();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Costable|Behavior")
	bool bIsConsumable = true;  // default true = one-time use



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

	UPROPERTY()
	TMap<FGameplayTag, int32> InitialCostBundle;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
