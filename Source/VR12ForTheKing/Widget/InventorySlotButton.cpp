// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/InventorySlotButton.h"

#include "../Component/InventoryComponent.h"
#include "../Character/MyCharacter.h"
#include "StatusWidget.h"

void UInventorySlotButton::NativeConstruct(UStatusWidget* NewStatusWidget)
{
	StatusWidget = NewStatusWidget;
	this->OnHovered.AddDynamic(this, &UInventorySlotButton::ButtonOnHovered);
	this->OnUnhovered.AddDynamic(this, &UInventorySlotButton::ButtonOnUnhovered);
	this->OnClicked.AddDynamic(this, &UInventorySlotButton::ButtonOnClicked);
}

void UInventorySlotButton::InitWidget(UInventoryComponent* NewOwnerInventory, int32 NewItemIndex)
{
	OwnerInventory = NewOwnerInventory;
	ItemIndex = NewItemIndex;
	FItem* ItemInfo = OwnerInventory->GetItemInfoAtInventory(ItemIndex);

	WidgetStyle.Normal.SetResourceObject(ItemInfo->ItemIcon);
	WidgetStyle.Hovered.SetResourceObject(ItemInfo->ItemIcon);
	WidgetStyle.Pressed.SetResourceObject(ItemInfo->ItemIcon);
}

void UInventorySlotButton::ButtonOnHovered()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s Hovered"), *this->GetName());
	StatusWidget->InitItemDetail(OwnerInventory->GetItemInfoAtInventory(ItemIndex));
}

void UInventorySlotButton::ButtonOnUnhovered()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s Hovered"), *this->GetName());
	StatusWidget->HideItemDetail();
}

void UInventorySlotButton::ButtonOnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Clicked"), *this->GetName());

	OwnerInventory->UseItem(ItemIndex);
}