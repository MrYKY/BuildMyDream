// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BBasicDataStructures.h"
#include "GameFramework/Actor.h"
#include "BShop.generated.h"

UCLASS()
class BUILDMYDREAM_API ABShop : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Info")
	UDataTable* SkillItemTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Info")
	UDataTable* BatteryItemTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Info")
	UDataTable* EngineItemTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element Info")
	UDataTable* IntelliDeviceItemTable;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FBItemInfo> CurrentShopItems;
	

	UPROPERTY(BlueprintReadOnly)
	FBItemInfo BoughtItem;

	int32 SkillItemIndex = 1;
	int32 BatteryItemIndex = 1;
	int32 EngineItemIndex = 1;
	int32 IntelliDeviceItemIndex = 1;


	// Sets default values for this actor's properties
	ABShop();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable,Category = "Shop Action")
	virtual void BuyItem(const FBItemInfo& ItemInfo);
	UFUNCTION(BlueprintCallable,Category = "Shop Action")
	virtual void UpdateItem();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
