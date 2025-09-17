// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrencyComponent.h"

#include "ICostable.h"
#include "MovieSceneTracksComponentTypes.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UCurrencyComponent::UCurrencyComponent(): CurrentCurrency(0), MaxCurrency(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	// You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("BoxComponent")); //Assigning an subobject of box comp
	BoxComponent->SetBoxExtent(FVector(74.0f, 125.0f, 100.0f));
	//get the root component of the owner/ attaches the box to it

	//set relative location of the box to the component
	BoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	//CurrencyBalances. = 0;
	

	// ...
}


void UCurrencyComponent::AddCurrency(int32 Amount, FGameplayTag CurrencyType)
{
	CurrencyBalances[CurrencyType] += Amount;//adds the new amount to the current currency
	FString stringResult = TEXT("");

	stringResult = stringResult.Appendf(TEXT("Current Currency: %d") ,CurrencyBalances[CurrencyType]);
	
	UKismetSystemLibrary::PrintString(this, stringResult, true, false,
		FColor::Red, 10, "AddedCurrency");//prints the result to the screen

	OnCurrencyChanged.Broadcast(CurrencyBalances[CurrencyType], Amount, true, CurrencyType);// broadcasts current current


	//TArray<int32> MyCurrencies = {1, 2, 3, 3, 3, 1}; EDU: a way to write array
/*   
	FString stringResult = TEXT("")
	for (int i = 0; i < MyCurrencies.Num(); i++)
	{
		stringResult = stringResult.Appendf(TEXT("Number_%d: %d, "), i + 1, MyCurrencies[i]);
	}
	
	UKismetSystemLibrary::PrintString(this, stringResult, true, false, FColor::Red, 10, "Currency");
*/	
}

bool UCurrencyComponent::SpendCurrency(int32 Amount, FGameplayTag CurrencyType)
{
	//if current currency is less than 0 or the amount will causes current currency to be 0 return
	//Note that some items can be free and be purchased while CurrentCurrency = 0
	if(!CurrencyType.IsValid())
	{
		return false;
	}
	if (CurrencyBalances[CurrencyType] < 0 || CurrencyBalances[CurrencyType] - Amount < 0) 
	{
		return false;
	}
	else
	{
		CurrencyBalances[CurrencyType] -= Amount;// reduces the currenct currency that is held

		FString stringResult = TEXT(""); //assigns text that shows current currency to var

		stringResult = stringResult.Appendf(TEXT("Current Currency: %d") ,CurrencyBalances[CurrencyType]);// appends resultString
		
		UKismetSystemLibrary::PrintString(this, stringResult, true, false,
			FColor::Red, 10, "SpentCurrency");

		OnCurrencyChanged.Broadcast(CurrencyBalances[CurrencyType], Amount, false, CurrencyType);// broadcasts current currency and deltaamount
		return true;
	}
}
bool UCurrencyComponent::CanAfford(int32 Amount)
{
	return true;
}

void UCurrencyComponent::Purchase(UObject* ObjectToBuy)
{
	//checks that the ObjectToBuy implments Costable interface. 
	bool bIsImplemented = ObjectToBuy->GetClass()->ImplementsInterface(UICostable::StaticClass());
	if (!bIsImplemented)
	{
		return;// if no, it returns
	}
	else
	{
		int32 Cost = IICostable::Execute_GetCost(ObjectToBuy);// calls the function that is implemented in obj
		FGameplayTag CurrencyCostType = IICostable::Execute_GetCostType(ObjectToBuy);
		if (Cost < 0)
			return;// if cost is less than 0, returns
		else
		{
			SpendCurrency(Cost,CurrencyCostType);// passes cost to the function of spendCurrncy
		}
	}
}


// Called when the game starts
void UCurrencyComponent::BeginPlay()
{
	Super::BeginPlay();

	//validates if owner exist, otherwise crash will happen
	if (AActor* Owner = GetOwner())
	{
		BoxComponent = NewObject<UBoxComponent>(Owner); //creates an object and assign to box component
		if (BoxComponent != nullptr){ //checks box component to be not null

			BoxComponent->RegisterComponent();
			BoxComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

			BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UCurrencyComponent::OverlapBegin);
			BoxComponent->OnComponentEndOverlap.AddDynamic(this, &UCurrencyComponent::OverlapEnd);
		}
	}

	
	// ...
}

void UCurrencyComponent::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Checks for the implementation of the otherClass that is overlapped
	//if implmented, tries to assign the Cost of the costable to a variable
	//The variable passes to the SpendCurrency()
	Purchase(OtherActor);
}

void UCurrencyComponent::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}


// Called every frame
void UCurrencyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

