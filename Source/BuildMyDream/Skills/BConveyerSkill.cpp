// Fill out your copyright notice in the Description page of Project Settings.


#include "BConveyerSkill.h"


// Sets default values
ABConveyerSkill::ABConveyerSkill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool ABConveyerSkill::ApplySkill()
{
	if(Board->BoardArray[SkillTargetRowCol[0]-1][SkillTargetRowCol[1]-1] != nullptr)
	{
		if(Board->BoardArray[SkillTargetRowCol[0]-1][SkillTargetRowCol[1]-1]->ElementType != EBElementType::Malfunction
			&& Board->BoardArray[SkillTargetRowCol[0]-1][SkillTargetRowCol[1]-1]->Movable)
		{
			Board->BoardArray[SkillTargetRowCol[0]-1][SkillTargetRowCol[1]-1]->MoveRange=3;
			return true;
		}
	}
	return false;
}

// Called when the game starts or when spawned
void ABConveyerSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABConveyerSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

