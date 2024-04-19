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
	// Sets default values for this actor's properties
	ABElement();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Delegates
	FOnElementClicked OnElementClickedDelegate;
	FOnElementReleased OnElementReleasedDelegate;

	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	int32 Col;
	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	int32 Row;
	
	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	EBElementType ElementType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Board Setting")
	UStaticMeshComponent* ElementMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Info")
	UDataTable* ElementTypeMeshTable;
	

	UFUNCTION(BlueprintCallable)
	void SetElementType(EBElementType NewType);
	UFUNCTION(BlueprintCallable)
	void SetElementMesh();

	void OnClicked();
	void OnReleased();
	void UpdateLocation(FVector Location);
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	bool bIsDragging = false;
};
