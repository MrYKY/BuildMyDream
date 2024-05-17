// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BElement.h"
#include "GameFramework/Actor.h"
#include "BBoard.generated.h"

class ABGameModeBase;

UCLASS()
class BUILDMYDREAM_API ABBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	
	UPROPERTY(EditDefaultsOnly, Category = "Board Setting")
	int32 BoardSize = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Board Setting")
	float TileSize = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Board Setting")
	TSubclassOf<AActor> ElementClass;
	
	TArray<TArray<TObjectPtr<ABElement>>> BoardArray;
	int32 EmptyCellCount = 0;

	TObjectPtr<ABGameModeBase> GameMode;
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	AActor* GenerateElementCell(int32 Row, int32 Col);

	UFUNCTION(BlueprintCallable)
	AActor* GenerateElement();

	UFUNCTION(BlueprintCallable)
	AActor* GenerateElementType(EBElementType Type);



	UFUNCTION(BlueprintCallable)
	bool RemoveElement(int32 Row, int32 Col);
	UFUNCTION()
	void RemoveElementRes(int32 Row, int32 Col);

	UFUNCTION(BlueprintCallable)
	bool PutElement(FVector Location, ABElement* Element);
	UFUNCTION()
	void PutElementRes(FVector Location, ABElement* Element);
	UFUNCTION()
	void LockRandomElement();
	UFUNCTION()
	void UpdateAllElementScore(ABElement* MovedElement);
	UFUNCTION()
	void UpdateAllElementLockRound(ABElement* MovedElement);


	ABBoard();
	virtual void Tick(float DeltaTime) override;

	
private:
	void GenerateBoard();
	TArray<int32> GetRowColByLocation(FVector Location) const;
	void BindDelegates(TObjectPtr<ABElement> Element);
	void SetElementLocation(TObjectPtr<ABElement> Element);
	bool TryMerge(TObjectPtr<ABElement> Element,bool bFirstCall);
	



};



