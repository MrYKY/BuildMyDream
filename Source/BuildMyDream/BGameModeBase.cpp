// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameModeBase.h"
#include "GlobalFuncLib.h"
#include "BBoard.h"
#include "BElement.h"


ABGameModeBase::ABGameModeBase()
{
	DefaultPawnClass = nullptr;
	OnMoveMadeDelegate.AddDynamic(this, &ABGameModeBase::OnMoveMade);
	OnMergeMadeDelegate.AddDynamic(this, &ABGameModeBase::OnMergeMade);
	OnStartButtonClickedDelegate.AddDynamic(this, &ABGameModeBase::StartGame);
	OnGameOverDelegate.AddDynamic(this, &ABGameModeBase::GameOver);
	OnMoveMadeDelegate.AddDynamic(this, &ABGameModeBase::IncreaseGameRound);
}

void ABGameModeBase::OnMoveMade(ABElement* MovedElement)
{
	Board->GenerateElement();
	
	double rand1 = FMath::RandRange(0.0f, 1.0f);
	if (rand1 <= MalFunctionProb)
	{
		Board->GenerateElementType(EBElementType::Malfunction);
	}
	
	double rand2 = FMath::RandRange(0.0f, 1.0f);
	if (rand2 <= MalFunctionProb)
	{
		Board->LockRandomElement();
	}
	MovedElement->ActHandlerComponent->OnMoved();
}

void ABGameModeBase::OnMergeMade(ABElement* MergedElement)
{
	MergedElement->ActHandlerComponent->OnMerged();
}



void ABGameModeBase::StartGame()
{
	for(int k = 0; k < 3; k++)
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
	
}

void ABGameModeBase::GameOver()
{
}

void ABGameModeBase::IncreaseGameRound(ABElement* MovedElement)
{
	GameRound++;
	if(GameRound >= GameMaxRound)
	{
		OnGameOverDelegate.Broadcast();
	}
	
}


void ABGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Shop = GetWorld()->SpawnActor<ABShop>(ShopClass);
		
	

}
