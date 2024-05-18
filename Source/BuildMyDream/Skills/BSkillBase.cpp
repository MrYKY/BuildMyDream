// Fill out your copyright notice in the Description page of Project Settings.


#include "BSkillBase.h"

#include "BuildMyDream/BGameModeBase.h"
#include "BuildMyDream/BGameStateBase.h"
#include "BuildMyDream/BPlayerController.h"


// Sets default values
ABSkillBase::ABSkillBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABSkillBase::TryApplySkill(TArray<int32> RowCol)
{
	SkillTargetRowCol = RowCol;
	if(GameState->ManpowerIndex>=ManPowerCost)
	{
		if(ApplySkill())
		{
			ConsumeManPower(ManPowerCost);
		}
	}
	Cast<ABPlayerController>(GetWorld()->GetFirstPlayerController())->bCastingSkill = false;
	this->Destroy();
}

bool ABSkillBase::ApplySkill()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Skill Applied"));
	if(Board->BoardArray[SkillTargetRowCol[0]-1][SkillTargetRowCol[1]-1] != nullptr)
	{
		if(Board->BoardArray[SkillTargetRowCol[0]-1][SkillTargetRowCol[1]-1]->ElementType == EBElementType::Malfunction)
		{
			Board->BoardArray[SkillTargetRowCol[0]-1][SkillTargetRowCol[1]-1]->Destroy();
			Board->BoardArray[SkillTargetRowCol[0]-1][SkillTargetRowCol[1]-1] = nullptr;
			Board->EmptyCellCount++;
			return true;
		}
	}
	return false;
}

void ABSkillBase::GetInfoNeed()
{
}

bool ABSkillBase::ConsumeManPower(int Consume)
{
	if(GameState->ManpowerIndex>=Consume)
	{
		GameState->AddScoreByType(EBElementType::Manpower, -Consume);
		return true;
	}else
	{
		return false;
	}
	
}


// Called when the game starts or when spawned
void ABSkillBase::BeginPlay()
{
	Super::BeginPlay();
	Cast<ABPlayerController>(GetWorld()->GetFirstPlayerController())->bCastingSkill = true;
	Cast<ABPlayerController>(GetWorld()->GetFirstPlayerController())->OnCastingSkillPointGetDelegate.AddDynamic(this, &ABSkillBase::TryApplySkill);
	Board = Cast<ABBoard>(Cast<ABGameModeBase>(GetWorld()->GetAuthGameMode())->Board);
	GameState = Cast<ABGameStateBase>(Cast<ABGameModeBase>(GetWorld()->GetAuthGameMode())->GameState);
	
}

// Called every frame
void ABSkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Cast<ABPlayerController>(GetWorld()->GetFirstPlayerController())->bCastingSkill)
	{
		FVector MouseLocation;
		FVector MouseDirection;
		Cast<ABPlayerController>(GetWorld()->GetFirstPlayerController())->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
		FVector NewLocation(MouseLocation.X, 100.0f, MouseLocation.Z-10.0f);
		SetActorLocation(NewLocation);
	}
}

