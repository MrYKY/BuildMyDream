// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameStateBase.h"

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
		break;
	case EBElementType::Manpower:
		ManpowerIndex += Score;
		break;
	case EBElementType::Technology:
		TechnologyIndex += Score;
		break;
	default:
		break;
	}
}

void ABGameStateBase::SetGameStage(EBGameStage NewGameStage)
{
	CurrentGameStage = NewGameStage;
}

void ABGameStateBase::BeginPlay()
{
	Super::BeginPlay();
}
