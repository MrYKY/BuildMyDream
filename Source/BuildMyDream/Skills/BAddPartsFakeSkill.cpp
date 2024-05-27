// Fill out your copyright notice in the Description page of Project Settings.


#include "BAddPartsFakeSkill.h"

#include "BuildMyDream/BGameModeBase.h"


// Sets default values
ABAddPartsFakeSkill::ABAddPartsFakeSkill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PartMesh"));
}

bool ABAddPartsFakeSkill::ApplySkill()
{
	if (Board->BoardArray[SkillTargetRowCol[0]-1][SkillTargetRowCol[1]-1]!=nullptr)
	{
		return false;
	}
	if(GameState->ProductivityIndex>=PartInfo.PartProductivityCost)
	{
		GameState->AddScoreByType(EBElementType::Productivity, -PartInfo.PartProductivityCost);
		ABElement* Part = Cast<ABElement>(Board->GenerateElementCell(SkillTargetRowCol[0],SkillTargetRowCol[1]));
		Part->SetElementType(EBElementType::End);
		Part->ElementMesh->SetStaticMesh(PartInfo.PartMesh);
		switch (PartInfo.CarPartType)
		{
		case EBCarPartType::Battery:
			GameState->CurrentBatteryLevel++;
			break;
		case EBCarPartType::Engine:
			GameState->CurrentEngineLevel++;
			break;
		case EBCarPartType::IntelliDevice:
			GameState->CurrentIntelliDeviceLevel++;
			break;
		default:
			break;
		}
		Cast<ABGameModeBase>(GetWorld()->GetAuthGameMode())->OnTargetPutDelegate.Broadcast();
		return true;
	}else
	{
		return false;
	}
}

void ABAddPartsFakeSkill::InitPartSkill(const FBItemInfo& PartInformation)
{
	PartInfo = PartInformation;
	PartMesh->SetStaticMesh(PartInformation.PartMesh);
}

// Called when the game starts or when spawned
void ABAddPartsFakeSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABAddPartsFakeSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

