// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CurrencyComponent.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurrencyChanged, float, CurrentCurrncy);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CURRENCYSYSTEM_API UCurrencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCurrencyComponent();

	UPROPERTY(EditAnywhere)
	int32 CurrentCurrency;
	UPROPERTY(EditAnywhere)
	int32 MaxCurrency;

	UPROPERTY(BlueprintAssignable)
	FCurrencyChanged OnCurrencyChanged;
	
	UFUNCTION(BlueprintCallable)
	void AddCurrency(int32 Amount);
	UFUNCTION(BlueprintCallable)
	bool SpendCurrency(int32 Amount);
	UFUNCTION(BlueprintCallable)
	bool CanAfford(int32 Amount);
	UFUNCTION(BlueprintCallable)
	void Purchase(UObject *ObjectToBuy);
	
	
	UPROPERTY()
    	UBoxComponent* BoxComponent;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult); // overlapBegin
	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex); // OverlapEnd
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
