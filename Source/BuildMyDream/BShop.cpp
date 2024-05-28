// Fill out your copyright notice in the Description page of Project Settings.


#include "BShop.h"

#include "BGameModeBase.h"


// Sets default values
ABShop::ABShop()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABShop::BeginPlay()
{
	Super::BeginPlay();	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Shop Created."));
	CurrentShopItems.SetNum(4);
	UpdateItem();
	
	
}

void ABShop::BuyItem(const FBItemInfo& ItemInfo)
{
	switch (ItemInfo.ItemType)
	{
	case EBItemType::Parts:
		switch (ItemInfo.CarPartType)
		{
		case EBCarPartType::Battery:
			BatteryItemIndex++;
			break;
		case EBCarPartType::Engine:
			EngineItemIndex++;
			break;
		case EBCarPartType::IntelliDevice:
			IntelliDeviceItemIndex++;
			break;
		default:
			break;
		}
		break;
	case EBItemType::Skill:
		SkillItemIndex++;
		break;
	default:
		break;
	}
	BoughtItem = ItemInfo;
	UpdateItem();
	Cast<ABGameModeBase>(GetWorld()->GetAuthGameMode())->OnItemBoughtDelegate.Broadcast();
}

void ABShop::UpdateItem()
{
	FBItemInfo* RowInfoPtr;
	RowInfoPtr = SkillItemTable->FindRow<FBItemInfo>(FName(*FString::Printf(TEXT("%d"), SkillItemIndex)), TEXT("Skill Not Found"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Try Read Skill Item."));
	if(RowInfoPtr)
	{
		CurrentShopItems[0] = *RowInfoPtr;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("Skill Item Read."));
	}
	else CurrentShopItems[0].ItemType = EBItemType::End;
	RowInfoPtr = BatteryItemTable->FindRow<FBItemInfo>(FName(*FString::Printf(TEXT("%d"), BatteryItemIndex)), TEXT(""));
	if(RowInfoPtr) CurrentShopItems[1] = *RowInfoPtr;
	else CurrentShopItems[1].ItemType = EBItemType::End;
	RowInfoPtr = EngineItemTable->FindRow<FBItemInfo>(FName(*FString::Printf(TEXT("%d"), EngineItemIndex)), TEXT(""));
	if(RowInfoPtr) CurrentShopItems[2] = *RowInfoPtr;
	else CurrentShopItems[2].ItemType = EBItemType::End;
	RowInfoPtr = IntelliDeviceItemTable->FindRow<FBItemInfo>(FName(*FString::Printf(TEXT("%d"), IntelliDeviceItemIndex)), TEXT(""));
	if(RowInfoPtr) CurrentShopItems[3] = *RowInfoPtr;
	else CurrentShopItems[3].ItemType = EBItemType::End;
	Cast<ABGameModeBase>(GetWorld()->GetAuthGameMode())->OnItemUpdatedDelegate.Broadcast();
}

// Called every frame
void ABShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

