// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BActHandlerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BUILDMYDREAM_API UBActHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	void OnMerged();
	void OnMoved();
	// Sets default values for this component's properties
	UBActHandlerComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
