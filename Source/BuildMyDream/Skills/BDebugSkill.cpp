// Fill out your copyright notice in the Description page of Project Settings.


#include "BDebugSkill.h"

#include "BuildMyDream/BGameModeBase.h"


// Sets default values
ABDebugSkill::ABDebugSkill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool ABDebugSkill::ApplySkill()
{
	if(Super::ApplySkill())
	{
		Cast<ABGameModeBase>(GetWorld()->GetAuthGameMode())->OnSkillCastedDelegate.Broadcast();
		return true;
	}
	return false;
}

// Called when the game starts or when spawned
void ABDebugSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABDebugSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

