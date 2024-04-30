// Fill out your copyright notice in the Description page of Project Settings.


#include "BHUD.h"

#include "Blueprint/UserWidget.h"

void ABHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ABHUD::BeginPlay()
{
	Super::BeginPlay();
	// Create Main Menu
	if(BMainMenuClass)
	{
		BMainMenu = CreateWidget<UUserWidget>(GetWorld(), BMainMenuClass);
		if(BMainMenu)
		{
			BMainMenu->AddToViewport();
		}
	}
	if (BHUD)
	{
		BHUD = CreateWidget<UUserWidget>(GetWorld(), BHUDClass);
	}
}

void ABHUD::SwitchUI(TObjectPtr<UUserWidget> NewUI, TObjectPtr<UUserWidget> OldUI)
{
	OldUI->RemoveFromParent();
	NewUI->AddToViewport();
}
