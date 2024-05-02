// Fill out your copyright notice in the Description page of Project Settings.


#include "BHUD.h"

#include "BGameModeBase.h"
#include "Blueprint/UserWidget.h"

void ABHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ABHUD::BeginPlay()
{
	Super::BeginPlay();
	// Bind Delegates

	Cast<ABGameModeBase>(GetWorld()->GetAuthGameMode())->OnStartButtonClickedDelegate.AddDynamic(this, &ABHUD::OnStartButtonClicked);

	
	// Create Widgets
	if(BMainMenuClass)
	{
		BMainMenu = CreateWidget<UUserWidget>(GetWorld(), BMainMenuClass);
		if(BMainMenu)
		{
			BMainMenu->AddToViewport();
		}
	}
	if (BHUDClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Creating HUD..."));
		BHUD = CreateWidget<UUserWidget>(GetWorld(), BHUDClass);
	}
	if (BShopUI)
	{
		BShopUI = CreateWidget<UUserWidget>(GetWorld(), BShopUIClass);
	}
}

void ABHUD::OnStartButtonClicked()
{
	SwitchUI(BHUD, BMainMenu);
}


void ABHUD::SwitchUI(TObjectPtr<UUserWidget> NewUI, TObjectPtr<UUserWidget> OldUI)
{
	if(OldUI)
	{
		OldUI->RemoveFromParent();
	}
	if(NewUI)
	{
		NewUI->AddToViewport();
	}
}
