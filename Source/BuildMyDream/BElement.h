// Fill out your copyright notice in the Description page of Project Settings.
// Element Shouldn't Know What It's Board Is. It's Board's responsibility to manage elements.

#pragma once

#include "CoreMinimal.h"
#include "BActHandlerComponent.h"
#include "GameFramework/Actor.h"
#include "BBasicDataStructures.h"
#include "BElement.generated.h"

// Delegate Indicates Element is clicked
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnElementClicked, int32, Col, int32, Row);
// Delegate Indicates Element is released
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnElementReleased, FVector, Location, ABElement*, Element);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCurrentScoreChanged);

// Element Shouldn't Know What It's Board Is. It's Board's responsibility to manage elements.
UCLASS()
class BUILDMYDREAM_API ABElement : public AActor
{
	GENERATED_BODY()

public:
	// 委托
	// Delegates
	FOnElementClicked OnElementClickedDelegate;
	FOnElementReleased OnElementReleasedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category="Delegates")
	FOnCurrentScoreChanged OnCurrentScoreChangedDelegate;

	// 组件
	// Components
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Board Setting")
	// UStaticMeshComponent* Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Board Setting")
	UStaticMeshComponent* ElementMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Board Setting")
	UBActHandlerComponent* ActHandlerComponent;
	

	// 常量
	// Properties
	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	int32 Col;
	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	int32 Row;

	int32 MoveRange = 1;
	int32 Level;
	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	int32 CurrentScore;
	int32 Level2ScoreRatio = 6;
	int32 MoveConsume = 1;
	
	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	EBElementType ElementType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Info")
	UDataTable* ElementTypeMeshTable;

	// 函数
	// Functions
	UFUNCTION(BlueprintCallable)
	void SetElementType(EBElementType NewType);
	
	UFUNCTION(BlueprintCallable)
	void SetElementMesh();

	UFUNCTION(BlueprintCallable)
	void SetElementLevel(int NewLevel);
	

	ABElement();
	virtual void Tick(float DeltaTime) override;
	void OnClicked();
	void OnReleased();
	void UpdateLocation(FVector Location);

protected:
	virtual void BeginPlay() override;
};
