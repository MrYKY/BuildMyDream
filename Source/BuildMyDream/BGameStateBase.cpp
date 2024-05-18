// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameStateBase.h"
#include "BGameModeBase.h"

ABGameStateBase::ABGameStateBase()
{
	// 初始化元素等级表
	// Initialize the element level map
	for(int i=0;i<static_cast<int>(EBElementType::End);i++)
	{
		ElementLevelMap.Add(static_cast<EBElementType>(i),1);
	}
}

void ABGameStateBase::AddScoreByType(EBElementType ElementType, int32 Score)
{
	switch (ElementType)
	{
	case EBElementType::Productivity:
		ProductivityIndex += Score;
		OnResourceChangedDelegate.Broadcast();
		if(ProductivityIndex<=0)
		{
			Cast<ABGameModeBase>(GetWorld()->GetAuthGameMode())->OnGameOverDelegate.Broadcast();
		}
		break;
	case EBElementType::Manpower:
		ManpowerIndex += Score;
		OnResourceChangedDelegate.Broadcast();
		break;
	case EBElementType::Technology:
		TechnologyIndex += Score;
		OnResourceChangedDelegate.Broadcast();
		break;
	default:
		break;
	}
}

void ABGameStateBase::SetGameStage(EBGameStage NewGameStage)
{
	CurrentGameStage = NewGameStage;
}

void ABGameStateBase::SetGameTarget(FName GameTargetID)
{
	// Get the game target data by targetID from the data table
	// Use the data to set the game target
	if(GameTaskTable)
	{
		FBTask* GameTaskRow = GameTaskTable->FindRow<FBTask>(GameTargetID, "");
		if(GameTaskRow)
		{
			BatteryLevelNeed = GameTaskRow->BatteryLevelNeed;
			EngineLevelNeed = GameTaskRow->EngineLevelNeed;
			IntelliDeviceLevelNeed = GameTaskRow->IntelliDeviceLevelNeed;
		}
	}
}

void ABGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	OnResourceChangedDelegate.Broadcast();
}
