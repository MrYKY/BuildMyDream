// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BBasicDataStructures.h"
#include "BGameStateBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceChanged);

UCLASS()
class BUILDMYDREAM_API ABGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "GameState")
	FOnResourceChanged OnResourceChangedDelegate;
	
	UPROPERTY(BlueprintReadWrite,Category = "GameState")
	int32 ProductivityIndex=20;
	UPROPERTY(BlueprintReadWrite, Category = "GameState")
	int32 ManpowerIndex;
	UPROPERTY(BlueprintReadWrite, Category = "GameState")
	int32 TechnologyIndex;

	UPROPERTY(EditDefaultsOnly, Category = "Task Info")
	int32 BatteryLevelNeed;
	UPROPERTY(EditDefaultsOnly, Category = "Task Info")
	int32 EngineLevelNeed;
	UPROPERTY(EditDefaultsOnly, Category = "Task Info")
	int32 IntelliDeviceLevelNeed;

	UPROPERTY(BlueprintReadWrite, Category = "Task Info")
	int32 CurrentBatteryLevel=0;
	UPROPERTY(BlueprintReadWrite, Category = "Task Info")
	int32 CurrentEngineLevel=0;
	UPROPERTY(BlueprintReadWrite, Category = "Task Info")
	int32 CurrentIntelliDeviceLevel=0;

	TMap<EBElementType,int32> ElementLevelMap;

	EBGameStage CurrentGameStage=EBGameStage::PowerStage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stage Info")
	UDataTable* GameTaskTable;
	
	
	ABGameStateBase();
	void AddScoreByType(EBElementType ElementType,int32 Score);
	void SetGameStage(EBGameStage NewGameStage);
	UFUNCTION(BlueprintCallable)
	void SetGameTarget(FName GameTargetID);
	virtual void BeginPlay() override;

};
