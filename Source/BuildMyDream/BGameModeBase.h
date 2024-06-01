// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BElement.h"
#include "BShop.h"
#include "GameFramework/GameModeBase.h"
#include "BGameModeBase.generated.h"

/**
 * 
 */



class ABBoard;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActMade,ABElement*, MergedElement);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);
UCLASS()
class BUILDMYDREAM_API ABGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ABGameModeBase();
public:
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnActMade OnMoveMadeDelegate;
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnActMade OnMergeMadeDelegate;
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnStartButtonClicked OnElementLiftedDelegate;
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnStartButtonClicked OnStartButtonClickedDelegate;
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnGameOver OnGameOverDelegate;
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnStartButtonClicked OnItemBoughtDelegate;
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnStartButtonClicked OnItemUpdatedDelegate;
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnStartButtonClicked OnSkillCastedDelegate;
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnStartButtonClicked OnTargetPutDelegate;
	

	UPROPERTY(BlueprintReadWrite, Category = "Board Setting")
	TObjectPtr<ABBoard> Board;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Board Setting")
	int32 GameMaxRound = 100;

	UPROPERTY(BlueprintReadWrite, Category = "Board Setting")
	int32 GameRound = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Board Setting")
	double MalFunctionProb = 0.10;

	UPROPERTY(EditDefaultsOnly,Category = "Shop")
	TSubclassOf<ABShop> ShopClass;

	UPROPERTY(BlueprintReadOnly,Category = "Shop")
	TObjectPtr<ABShop> Shop;
	
	UFUNCTION(BlueprintCallable)
	virtual void OnMoveMade(ABElement* MovedElement);

	UFUNCTION(BlueprintCallable)
	virtual void OnMergeMade(ABElement* MergedElement);

	UFUNCTION()
	virtual void StartGame();
	
	UFUNCTION()
	virtual void GameOver();

	UFUNCTION()
	void IncreaseGameRound(ABElement* MovedElement);

	virtual void BeginPlay() override;
};
