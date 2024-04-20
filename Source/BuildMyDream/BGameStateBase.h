// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class BUILDMYDREAM_API ABGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	int32 WheelIndex;
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	int32 EngineIndex;
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	int32 BatteryIndex;

};
