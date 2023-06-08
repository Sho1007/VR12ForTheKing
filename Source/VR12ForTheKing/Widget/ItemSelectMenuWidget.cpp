// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/ItemSelectMenuWidget.h"

#include "Components/Button.h"
#include "../Item/ItemBase.h"
#include "../Component/InventoryComponent.h"
#include "../Character/MyCharacter.h"

void UItemSelectMenuWidget::NativeConstruct()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
	Btn_Use->OnClicked.AddDynamic(this, &UItemSelectMenuWidget::UseButtonOnClicked);
	Btn_Equip->OnClicked.AddDynamic(this, &UItemSelectMenuWidget::EquipButtonOnClicked);
	Btn_Close->OnClicked.AddDynamic(this, &UItemSelectMenuWidget::CloseButtonOnClicked);
}

void UItemSelectMenuWidget::InitWidget(AMyCharacter* NewOwnerCharacter, int32 NewItemIndex)
{
	OwnerCharacter = NewOwnerCharacter;
	ItemIndex = NewItemIndex;

	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(OwnerCharacter->FindComponentByClass(UInventoryComponent::StaticClass()));
	checkf(InventoryComponent != nullptr, TEXT("OwnerCharacter has not Inventory Component"));

	FItemInstance& ItemInstance = InventoryComponent->GetItemArray()[ItemIndex];
	FItem* ItemInfo = InventoryComponent->GetItemInfoAtInventory(ItemIndex);

	Btn_Equip->SetVisibility(ESlateVisibility::HitTestInvisible);
	Btn_Use->SetVisibility(ESlateVisibility::HitTestInvisible);
	if (ItemInfo->ItemType == EItemType::EQUIPMENT)
	{
		Btn_Equip->SetVisibility(ESlateVisibility::Visible);
	}
	else if (ItemInfo->ItemType == EItemType::CONSUMABLE)
	{
		Btn_Use->SetVisibility(ESlateVisibility::Visible);
	}

	this->SetVisibility(ESlateVisibility::Visible);
}

void UItemSelectMenuWidget::CloseButtonOnClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UItemSelectMenuWidget::UseButtonOnClicked()
{
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(OwnerCharacter->FindComponentByClass(UInventoryComponent::StaticClass()));
	checkf(InventoryComponent != nullptr, TEXT("OwnerCharacter has not Inventory Component"));
	InventoryComponent->UseItem(ItemIndex);
	
	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UItemSelectMenuWidget::EquipButtonOnClicked()
{
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(OwnerCharacter->FindComponentByClass(UInventoryComponent::StaticClass()));
	checkf(InventoryComponent != nullptr, TEXT("OwnerCharacter has not Inventory Component"));
	InventoryComponent->EquipItem(ItemIndex);

	this->SetVisibility(ESlateVisibility::Collapsed);
}