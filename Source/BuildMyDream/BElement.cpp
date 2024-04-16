// Fill out your copyright notice in the Description page of Project Settings.


#include "BElement.h"


// Sets default values
ABElement::ABElement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Randomly set the ElementType
	ElementType = static_cast<EBElementType>(FMath::RandRange(0, 2));
	ElementMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));
	RootComponent = ElementMesh;

}

void ABElement::OnClicked()
{
	bIsDragging = true;
	FVector NewLocation(GetActorLocation().X, GetActorLocation().Y+100.0f, GetActorLocation().Z);
	SetActorLocation(NewLocation);
}

void ABElement::OnReleased()
{
	bIsDragging = false;
	Board->PutElement(GetActorLocation(), this);
}

void ABElement::UpdateLocation(FVector Location)
{
	SetActorLocation(Location);
}


// Called when the game starts or when spawned
void ABElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

