// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSkillBase.h"
#include "BDebugSkill.generated.h"

UCLASS()
class BUILDMYDREAM_API ABDebugSkill : public ABSkillBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABDebugSkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};