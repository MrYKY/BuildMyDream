// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BHUD.generated.h"

/**
 * 
 */
UCLASS()
class BUILDMYDREAM_API ABHUD : public AHUD
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, Category = "HUD Setting")
	TSubclassOf<UUserWidget> BMainMenuClass;
	TObjectPtr<UUserWidget> BMainMenu;
	
	UPROPERTY(EditDefaultsOnly, Category = "HUD Setting")
	TSubclassOf<UUserWidget> BHUDClass;
	TObjectPtr<UUserWidget> BHUD;
	
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	void SwitchUI(TObjectPtr<UUserWidget> NewUI, TObjectPtr<UUserWidget> OldUI);
};
