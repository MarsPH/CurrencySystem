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

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent")); //Assigning an subobject of box comp
	BoxComponent->SetBoxExtent(FVector(150.0f, 150.0f, 150.0f));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("WidgetComponent"));
	WidgetComponent-> SetRelativeLocation(FVector(0, 0, 100));
	WidgetComponent->Text

	


}

int32 ACostable::GetCost_Implementation()
{
	return Cost;
}



// Called when the game starts or when spawned
void ACostable::BeginPlay()
{
	Super::BeginPlay();

		RootComponent = GetRootComponent();
		BoxComponent = NewObject<UBoxComponent>(RootComponent); //creates an object and assign to box component
		if (BoxComponent != nullptr){ //checks box component to be not null

			BoxComponent->RegisterComponent();
			BoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

			BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACostable::OverlapBegin);// bind begin overlap
			BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACostable::OverlapEnd);// bind end overlap
		}

		WidgetComponent = NewObject<UWidgetComponent>(RootComponent);
		if (WidgetComponent != nullptr)
		{
			WidgetComponent->RegisterComponent();//creates the physical state
			WidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			WidgetComponent->SetHiddenInGame(true);//it only is visible under conditions
		}
	
}

void ACostable::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		WidgetComponent->SetHiddenInGame(false);
}

void ACostable::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	WidgetComponent->SetHiddenInGame(true);
}


// Called every frame
void ACostable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

