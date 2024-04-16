// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BBoard.h"
#include "GameFramework/Actor.h"
#include "BElement.generated.h"

UENUM(BlueprintType)
enum class EBElementType : uint8
{
	Battery,
	Wheel,
	Engine,
};

UCLASS()
class BUILDMYDREAM_API ABElement : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABElement();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	int32 Col;
	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	int32 Row;
	
	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	EBElementType ElementType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Board Setting")
	UStaticMeshComponent* ElementMesh;

	UPROPERTY(BlueprintReadOnly, Category = "Element Info")
	ABBoard *Board = nullptr;

	void OnClicked();
	void OnReleased();
	void UpdateLocation(FVector Location);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	bool bIsDragging = false;
};
