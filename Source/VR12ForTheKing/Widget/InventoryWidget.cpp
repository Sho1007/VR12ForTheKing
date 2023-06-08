// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/InventoryWidget.h"

#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"


#include "../Character/MyCharacter.h"
#include "../Component/InventoryComponent.h"
#include "../Widget/InventoryItemListSlot.h"

void UInventoryWidget::NativeConstruct()
{
	EquipmentNameArray.Add(TB_WeaponSlotName);
	EquipmentNameArray.Add(TB_ShieldSlotName);
	EquipmentNameArray.Add(TB_HeadgearSlotName);
	EquipmentNameArray.Add(TB_ArmorSlotName);
	EquipmentNameArray.Add(TB_FootwearSlotName);
	EquipmentNameArray.Add(TB_NecklaceSlotName);
	EquipmentNameArray.Add(TB_TrinketSlotName);
}

void UInventoryWidget::InitWidget(UStatusWidget* StatusWidget, AMyCharacter* NewTargetCharacter)
{
	TargetCharacter = NewTargetCharacter;
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(TargetCharacter->GetComponentByClass(UInventoryComponent::StaticClass()));
	checkf(InventoryComponent != nullptr, TEXT("Target Character has not InventoryComponent"));
	TArray<FItemInstance>& ItemArray = InventoryComponent->GetItemArray();
	TArray<FItemInstance>& EquipmentSlot = InventoryComponent->GetEquipmentSlot();

	// Init EquipmentSlot
	
	for (int i = 1; i < EquipmentSlot.Num() - 1; ++i)
	{
		if (EquipmentSlot[i].ItemRow.IsNone())
		{
			EquipmentNameArray[i - 1]->SetText(FText());
		}
		else
		{
			FItem* ItemInfo = InventoryComponent->GetItemInfo(EquipmentSlot[i].ItemRow);
			checkf(ItemInfo != nullptr, TEXT("Cannot find Item in DataTable"));

			EquipmentNameArray[i - 1]->SetText(ItemInfo->ItemName);
		}
	}
	
	// Init ItemList
	VB_ItemList->ClearChildren();

	checkf(InventoryItemListSlotClass != nullptr, TEXT("InventoryItemListSlotClass is not valid"));

	for (int i = 0; i < ItemArray.Num(); ++i)
	{
		UInventoryItemListSlot* InventoryItemListSlot = CreateWidget<UInventoryItemListSlot>(GetWorld()->GetFirstPlayerController(), InventoryItemListSlotClass);
		VB_ItemList->AddChildToVerticalBox(InventoryItemListSlot);
		InventoryItemListSlot->InitWidget(StatusWidget, TargetCharacter, i);
	}
}