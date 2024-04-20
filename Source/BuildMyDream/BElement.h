// Fill out your copyright notice in the Description page of Project Settings.
// Element Shouldn't Know What It's Board Is. It's Board's responsibility to manage elements.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BElement.generated.h"

// Delegate Indicates Element is clicked
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnElementClicked, int32, Col, int32, Row);
// Delegate Indicates Element is released
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnElementReleased, FVector, Location, ABElement*, Element);

UENUM(BlueprintType)
enum class EBElementType : uint8
{
	Battery,
	Wheel,
	Engine,
};

USTRUCT(BlueprintType)
struct FElementInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	EBElementType ElementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	UStaticMesh* ElementMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	FVector MeshScale = FVector(1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	FRotator MeshRotation = FRotator(0.0f, 0.0f, 0.0f);
};


// Element Shouldn't Know What It's Board Is. It's Board's responsibility to manage elements.
UCLASS()
class BUILDMYDREAM_API ABElement : public AActor
{
	GENERATED_BODY()

public:
	//Delegates
	FOnElementClicked OnElementClickedDelegate;
	FOnElementReleased OnElementReleasedDelegate;

	// Properties
	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	int32 Col;
	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	int32 Row;

	int32 MoveRange = 1;
	
	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	EBElementType ElementType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Board Setting")
	UStaticMeshComponent* ElementMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Info")
	UDataTable* ElementTypeMeshTable;

	// Functions
	UFUNCTION(BlueprintCallable)
	void SetElementType(EBElementType NewType);
	
	UFUNCTION(BlueprintCallable)
	void SetElementMesh();

	ABElement();
	virtual void Tick(float DeltaTime) override;
	void OnClicked();
	void OnReleased();
	void UpdateLocation(FVector Location);

protected:
	virtual void BeginPlay() override;
};
