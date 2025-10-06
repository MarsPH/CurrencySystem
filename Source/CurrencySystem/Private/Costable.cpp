// Fill out your copyright notice in the Description page of Project Settings.


#include "Costable.h"

#include "DiffUtils.h"
#include "EditorCategoryUtils.h"
#include "ICostDisplayable.h"
#include "PassiveIncomeSource.h"
#include "Chaos/Deformable/ChaosDeformableCollisionsProxy.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACostable::ACostable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent")); //Assigning an subobject of box comp
	BoxComponent->SetBoxExtent(FVector(150.0f, 150.0f, 150.0f));
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("WidgetComponent"));
	
}

int32 ACostable::GetCost_Implementation()
{
	return Cost; // not used only in UI
}

TMap<FGameplayTag, int32> ACostable::GetCostBundle_Implementation()
{
	return CostBundle;//returns the cost bundle of this costable
}

void ACostable::SetCostBundle_Implementation(const TMap<FGameplayTag, int32>& bundle)
{
	isEmpty = false;
	for (const auto& Elem: bundle)
	{
		CostBundle.FindOrAdd(Elem.Key) += Elem.Value;
	}
	if (WidgetComponent)
	{
		UpdateWidget();
	}
}

void ACostable::EmptyBank_Implementation()
{
	for(auto& Elem : CostBundle)
	{
		Elem.Value = 0;
	}
	isEmpty = true;
}

bool ACostable::IsEmptiable_Implementation()
{
	return isEmptiable;
}

bool ACostable::GetIsEmpty_Implementation()
{
	return isEmpty;
}

void ACostable::SetIsEmpty_Implementation(bool isEmptyInput)
{
	isEmpty = isEmptyInput;
	UpdateWidget();
}


void ACostable::UpdateWidget()
{
	if (UUserWidget* Widget = WidgetComponent->GetUserWidgetObject())
	{
		if (Widget->GetClass()->ImplementsInterface(UICostDisplayable::StaticClass()))
		{
			IICostDisplayable::Execute_SetCostToDisplay(Widget, CostBundle);
			UKismetSystemLibrary::PrintString(this, Widget->GetName());
		}
	}
}

// Called when the game starts or when spawned
void ACostable::BeginPlay()
{
	Super::BeginPlay();
	

	RootComponent = GetRootComponent();
	//BoxComponent = NewObject<UBoxComponent>(RootComponent); //creates an object and assign to box component
	if (BoxComponent != nullptr){ //checks box component to be not null

		//BoxComponent->RegisterComponent();
		//box component cant attach to itself
		//BoxComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

		//BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACostable::OverlapBegin);// bind begin overlap
		//BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACostable::OverlapEnd);// bind end overlap
	}

	//WidgetComponent = NewObject<UWidgetComponent>(RootComponent);
	if (WidgetComponent != nullptr)
	{
		WidgetComponent->RegisterComponent();//creates the physical state
		WidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		WidgetComponent-> SetRelativeLocation(FVector(0, -85,0 ));

		//WidgetComponent->SetHiddenInGame(true);//it only is visible under conditions
	}
	if (WidgetComponent)
	{
		UpdateWidget();
	}

	
		//WidgetComponent->InitWidget();

		//checks that the ObjectToBuy implments Costable interface. 
		
	
	
	
	
}

void ACostable::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
		//WidgetComponent->SetHiddenInGame(false);
}

void ACostable::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	//WidgetComponent->SetHiddenInGame(true);
}

void ACostable::OnWidgetReady()
{
}


// Called every frame
void ACostable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACostable::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	
	
}

