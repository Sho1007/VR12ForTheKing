// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/InventoryItemListSlot.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "../Component/InventoryComponent.h"
#include "../Character/MyCharacter.h"
#include "StatusWidget.h"

void UInventoryItemListSlot::InitWidget(UStatusWidget* NewStatusWidget, AMyCharacter* NewOwnerCharacter, int32 NewItemIndex)
{
	StatusWidget = NewStatusWidget;
	OwnerCharacter = NewOwnerCharacter;
	ItemIndex = NewItemIndex;

	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(OwnerCharacter->FindComponentByClass(UInventoryComponent::StaticClass()));
	checkf(InventoryComponent != nullptr, TEXT("OwnerCharacter has not InventoryComponent"));
	
	FItemInstance& ItemInstance = InventoryComponent->GetItemArray()[ItemIndex];
	ItemInfo = InventoryComponent->GetItemInfoAtInventory(ItemIndex);

	Img_ItemIcon->SetBrushFromTexture(ItemInfo->ItemIcon);
	TB_ItemName->SetText(ItemInfo->ItemName);
	TB_ItemCount->SetText(FText::FromString(FString::FromInt(ItemInstance.CurrentStackCount)));
}

void UInventoryItemListSlot::NativeConstruct()
{
	Btn_Item->OnClicked.AddDynamic(this, &UInventoryItemListSlot::ButtonOnClicked);
	Btn_Item->OnHovered.AddDynamic(this, &UInventoryItemListSlot::ButtonOnHovered);
	Btn_Item->OnUnhovered.AddDynamic(this, &UInventoryItemListSlot::ButtonOnUnhovered);
}

void UInventoryItemListSlot::ButtonOnClicked()
{
	StatusWidget->InitItemSelectMenu(OwnerCharacter, ItemIndex);
}

void UInventoryItemListSlot::ButtonOnHovered()
{
	StatusWidget->InitItemDetail(ItemInfo);
}

void UInventoryItemListSlot::ButtonOnUnhovered()
{
	StatusWidget->HideItemDetail();
}