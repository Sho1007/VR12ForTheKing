// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/EquipSelectMenuWidget.h"

#include "Components/Button.h"

#include "../Component/InventoryComponent.h"
#include "../Character/MyCharacter.h"

void UEquipSelectMenuWidget::NativeConstruct()
{
	Btn_Unequip->OnClicked.AddDynamic(this, &UEquipSelectMenuWidget::UnequipButtonOnClicked);
	Btn_Close->OnClicked.AddDynamic(this, &UEquipSelectMenuWidget::CloseButtonOnClicked);

	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UEquipSelectMenuWidget::InitWidget(AMyCharacter* NewOwnerCharacter, int32 NewSlotIndex)
{
	OwnerCharacter = NewOwnerCharacter;
	SlotIndex = NewSlotIndex;
	this->SetVisibility(ESlateVisibility::Visible);
}

void UEquipSelectMenuWidget::UnequipButtonOnClicked()
{
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(OwnerCharacter->FindComponentByClass(UInventoryComponent::StaticClass()));
	checkf(InventoryComponent != nullptr, TEXT("OwnerCharacter has not Inventory Component"));

	InventoryComponent->UnEquipItem((EEquipmentType)SlotIndex);

	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UEquipSelectMenuWidget::CloseButtonOnClicked()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}