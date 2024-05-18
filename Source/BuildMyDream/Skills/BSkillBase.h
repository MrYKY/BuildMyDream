// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildMyDream/BBoard.h"
#include "BuildMyDream/BGameStateBase.h"
#include "GameFramework/Actor.h"
#include "BSkillBase.generated.h"

UCLASS()
class BUILDMYDREAM_API ABSkillBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABSkillBase();

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	FName SkillName;
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	int32 ManPowerCost = 10;
	
	
	TArray<int32> SkillTargetRowCol;
	
	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual void TryApplySkill(TArray<int32> RowCol);
	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual bool ApplySkill();
	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual void GetInfoNeed();
	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual bool ConsumeManPower(int Consume);

	TObjectPtr<ABBoard> Board;
	ABGameStateBase* GameState;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
