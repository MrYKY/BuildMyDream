// Fill out your copyright notice in the Description page of Project Settings.


#include "BElement.h"


ABElement::ABElement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ElementMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));
	// Randomly set the ElementType
	ElementType = static_cast<EBElementType>(FMath::RandRange(0, 2));
}


void ABElement::OnClicked()
{
	bIsDragging = true;
	// Board->RemoveElement(Row,Col);
	OnElementClickedDelegate.Broadcast(Row,Col);
	// FVector NewLocation(GetActorLocation().X, GetActorLocation().Y+100.0f, GetActorLocation().Z);
	// SetActorLocation(NewLocation);
}

void ABElement::OnReleased()
{
	bIsDragging = false;
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MouseRealsed"));
	// Board->PutElement(GetActorLocation(), this);
	OnElementReleasedDelegate.Broadcast(GetActorLocation(), this);
}

void ABElement::UpdateLocation(FVector Location)
{
	SetActorLocation(Location);
}

void ABElement::SetElementType(EBElementType NewType)
{
	ElementType = NewType;
}

void ABElement::SetElementMesh()
{
	if (ElementTypeMeshTable)
	{
		FElementInfoRow* RowInd = ElementTypeMeshTable->FindRow<FElementInfoRow>(FName(*FString::Printf(TEXT("%d"), static_cast<int32>(ElementType))), TEXT(""));
		if (RowInd->ElementMesh)
		{
			ElementMesh->SetStaticMesh(RowInd->ElementMesh);
			ElementMesh->SetRelativeScale3D(RowInd->MeshScale);
			ElementMesh->SetRelativeRotation(RowInd->MeshRotation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Element type not found in the table!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Element Type Mesh Table is not assigned!"));
	}
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

