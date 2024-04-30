// Fill out your copyright notice in the Description page of Project Settings.


#include "BActHandlerComponent.h"

#include "BElement.h"
#include "BGameStateBase.h"


void UBActHandlerComponent::OnMerged()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Handle Merge Event!"));
	Cast<ABGameStateBase>(GetWorld()->GetGameState())
	->AddScoreByType(Cast<ABElement>(GetOwner())->ElementType,
		Cast<ABElement>(GetOwner())->CurrentScore);
}

void UBActHandlerComponent::OnMoved()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Handle Move Event!"));
	if(Cast<ABElement>(GetOwner())->CurrentScore > Cast<ABElement>(GetOwner())->Level)
	{
		Cast<ABElement>(GetOwner())->CurrentScore--;
	}
}

// Sets default values for this component's properties
UBActHandlerComponent::UBActHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBActHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBActHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

