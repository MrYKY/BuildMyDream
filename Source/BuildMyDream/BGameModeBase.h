// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BElement.h"
#include "GameFramework/GameModeBase.h"
#include "BGameModeBase.generated.h"

/**
 * 
 */



class ABBoard;
// Delegete That Indicate A Move Is Made
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveMade,ABElement*,MovedElement);
// Delegate That Indicate A Merge Is Made
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMergeMade,ABElement*,MergedElement);

UCLASS()
class BUILDMYDREAM_API ABGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ABGameModeBase();
public:
	FOnMoveMade OnMoveMadeDelegate;
	FOnMergeMade OnMergeMadeDelegate;

	UPROPERTY(BlueprintReadWrite, Category = "Board Setting")
	TObjectPtr<ABBoard> Board;
	
	UFUNCTION(BlueprintCallable)
	virtual void OnMoveMade(ABElement* MovedElement);

	UFUNCTION(BlueprintCallable)
	virtual void OnMergeMade(ABElement* MergedElement);

	UFUNCTION(BlueprintCallable)
	virtual void StartGame();

	virtual void BeginPlay() override;
};
