#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CostableRestorer.generated.h"

class ACostable;
class UBoxComponent;

UCLASS()
class CURRENCYSYSTEM_API ACostableRestorer : public AActor
{
	GENERATED_BODY()

public:
	ACostableRestorer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* TriggerBox;

public:
	// 🔹 Allow restoring multiple costables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Restorer")
	TArray<ACostable*> TargetCostables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Restorer")
	bool bRestoreOnOverlap = true;

	// 🔹 Optional: restore delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Restorer")
	float RestoreDelay = 0.f;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);

	// 🔹 Restore all costables at once
	UFUNCTION(BlueprintCallable, Category="Restorer")
	void RestoreAll();
};
