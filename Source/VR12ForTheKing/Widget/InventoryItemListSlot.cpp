// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/InventoryItemListSlot.h"

#include "Components/TextBlock.h"

#include "../Component/InventoryComponent.h"

void UInventoryItemListSlot::InitWidget(FItem* NewItem, FItemInstance* NewItemInstance)
{
	TB_ItemName->SetText(NewItem->ItemName);
	TB_ItemCount->SetText(FText::FromString(FString::FromInt(NewItemInstance->CurrentStackCount)));
}