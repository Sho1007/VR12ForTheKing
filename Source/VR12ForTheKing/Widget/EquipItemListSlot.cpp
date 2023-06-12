// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/EquipItemListSlot.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "../Item/ItemBase.h"
#include "StatusWidget.h"
#include "../Character/MyCharacter.h"
#include "../Component/InventoryComponent.h"

void UEquipItemListSlot::InitWidget(AMyCharacter* NewOwnerCharacter)
{
	OwnerCharacter = NewOwnerCharacter;

	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(OwnerCharacter->FindComponentByClass(UInventoryComponent::StaticClass()));
	checkf(InventoryComponent != nullptr, TEXT("OwnerCharacter has not Inventory Component"));

	ItemInfo = InventoryComponent->GetEquipItemInfo(SlotIndex);

	if (ItemInfo == nullptr)
	{
		TB_EquipItemName->SetText(FText());
		this->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		TB_EquipItemName->SetText(ItemInfo->ItemName);
		this->SetVisibility(ESlateVisibility::Visible);
	}
}

void UEquipItemListSlot::NativeConstruct()
{
	Btn_EquipItem->OnClicked.AddDynamic(this, &UEquipItemListSlot::OnClicked);
	Btn_EquipItem->OnHovered.AddDynamic(this, &UEquipItemListSlot::OnHovered);
	Btn_EquipItem->OnUnhovered.AddDynamic(this, &UEquipItemListSlot::OnUnhovered);
}

void UEquipItemListSlot::OnClicked()
{
	StatusWidget->InitEquipSelectMenu(OwnerCharacter, SlotIndex);
}

void UEquipItemListSlot::OnHovered()
{
	StatusWidget->InitItemDetail(ItemInfo);
}

void UEquipItemListSlot::OnUnhovered()
{
	StatusWidget->HideItemDetail();
}

void UEquipItemListSlot::SetSlotIndex(UStatusWidget* NewStatusWidget, int32 NewSlotIndex)
{
	StatusWidget = NewStatusWidget;
	SlotIndex = NewSlotIndex;
	Img_EquipItemIcon->SetBrushFromTexture(SlotIcon);
}