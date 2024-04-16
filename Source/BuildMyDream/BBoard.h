// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBoard.generated.h"

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

	TArray<TArray<AActor*>> BoardArray;
	
	// Sets default values for this actor's properties
	ABBoard();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	bool GenerateElement(int32 Row, int32 Col);

	UFUNCTION(BlueprintCallable)
	bool RemoveElement(int32 Row, int32 Col);

	UFUNCTION(BlueprintCallable)
	bool PutElement(FVector Location, AActor* Element);


private:
	void GenerateBoard();
	TArray<int32> GetRowColByLocation(FVector Location);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
