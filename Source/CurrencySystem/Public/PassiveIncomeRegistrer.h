// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PassiveCostComponent.h"
#include "GameFramework/Actor.h"
#include "PassiveIncomeRegistrer.generated.h"

class UBoxComponent;

UCLASS()
class CURRENCYSYSTEM_API APassiveIncomeRegistrer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APassiveIncomeRegistrer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UBoxComponent* TriggerBox;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Registrer")
	TArray<ACostable*> PassiveSourcesToRegister;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Registrer")
	bool RegisterOnOverlap = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Registrer")
	bool IsRegistered = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Registrer")
	float LastToggleTime = 0.0f;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
					UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
					const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category="Registrer")
	void Register();
	UFUNCTION(BlueprintCallable, Category="Registrer")
	void Unregister();

};
