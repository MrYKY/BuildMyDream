// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BPlayerController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCastingSkillPointGet,TArray<int32>,RowCol);


UCLASS()
class BUILDMYDREAM_API ABPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	FOnCastingSkillPointGet OnCastingSkillPointGetDelegate;

	TObjectPtr<AActor> DraggingPiece = nullptr;

	FTimerDelegate TickDelegate;
	FTimerHandle TimerHandle;

	bool bCastingSkill = false;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;

	void OnLeftRelease();
	UFUNCTION()
	void FollowCursor() const;
	void OnLeftClick();

private:
	bool bIsDragging = false;
	bool bAllowDrag = true;
	
};
