// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameModeBase.h"

#include "BBoard.h"
#include "BElement.h"


ABGameModeBase::ABGameModeBase()
{
	DefaultPawnClass = nullptr;
	OnMoveMadeDelegate.AddDynamic(this, &ABGameModeBase::OnMoveMade);
	OnMergeMadeDelegate.AddDynamic(this, &ABGameModeBase::OnMergeMade);
	OnStartButtonClickedDelegate.AddDynamic(this, &ABGameModeBase::StartGame);
}

void ABGameModeBase::OnMoveMade(ABElement* MovedElement)
{
	Board->GenerateElement();
	MovedElement->ActHandlerComponent->OnMoved();
}

void ABGameModeBase::OnMergeMade(ABElement* MergedElement)
{
	MergedElement->ActHandlerComponent->OnMerged();
}



void ABGameModeBase::StartGame()
{
	for(int i = 0; i < 3; ++i)
	{
		AActor* NewElement = Board->GenerateElement();
		ABElement* Element = Cast<ABElement>(NewElement);
		// Set the i-th type of element
		Element->ElementType = static_cast<EBElementType>(i);
		Element->SetElementMesh();
		
	}
}

void ABGameModeBase::GameOver()
{
}

void ABGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	

}
