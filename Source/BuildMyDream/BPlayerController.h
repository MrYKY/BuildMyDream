// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BUILDMYDREAM_API ABPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	TObjectPtr<AActor> DraggingPiece = nullptr;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;

	void OnLeftRelease();
	void OnLeftClick();

private:
	bool bIsDragging = false;
};
