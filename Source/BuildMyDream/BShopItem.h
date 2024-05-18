// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BBasicDataStructures.h"
#include "UObject/Object.h"
#include "BShopItem.generated.h"

/**
 * 
 */
UCLASS()
class BUILDMYDREAM_API UBShopItem : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info")
	UDataTable* ItemDataTable;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Info")
	FName ItemID;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Info")
	EBItemType ItemType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Info")
	FText ItemName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Info")
	FText ItemDescription;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Info")
	int32 ItemTechCost;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Info")
	UTexture2D* ItemIcon;

	UFUNCTION(BlueprintCallable)
	void InitializeItem(FName ItemIdentity);
	
	UFUNCTION(BlueprintCallable)
	void GetSold();
};
