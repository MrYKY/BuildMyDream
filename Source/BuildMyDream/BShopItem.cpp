// Fill out your copyright notice in the Description page of Project Settings.


#include "BShopItem.h"


void UBShopItem::InitializeItem(FName ItemIdentity)
{
	// Get the item data by itemID from the data table
	// Use the data to initialize the item
	if(ItemDataTable)
	{
		FBItemInfo* ItemRow = ItemDataTable->FindRow<FBItemInfo>(ItemIdentity, "");

			if(ItemRow)
			{
				this->ItemID = ItemRow->ItemID;
				this->ItemType = ItemRow->ItemType;
				this->ItemName = ItemRow->ItemName;
				this->ItemDescription = ItemRow->ItemDescription;
				this->ItemTechCost = ItemRow->ItemTechCost;
				this->ItemIcon = ItemRow->ItemIcon;
			}
	}
}

void UBShopItem::GetSold()
{
}
