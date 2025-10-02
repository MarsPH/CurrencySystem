// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDepositType : uint8
{
	IntoBank UMETA(DisplayName="IntoBank"),
	IntoCurrency UMETA(DisplayName="IntoCurrency")
};

/**
 * 
 */
class CURRENCYSYSTEM_API EconomyTypes
{
public:
	EconomyTypes();
	~EconomyTypes();
};
