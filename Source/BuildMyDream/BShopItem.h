// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BShopItem.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UBShopItem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BUILDMYDREAM_API IBShopItem
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	int32 DemandTech;
	
	void GetSold();
};
