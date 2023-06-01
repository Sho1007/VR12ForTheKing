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

void UInventoryWidget::InitWidget(AMyCharacter* NewTargetCharacter)
{
	TargetCharacter = NewTargetCharacter;
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(TargetCharacter->GetComponentByClass(UInventoryComponent::StaticClass()));
	checkf(InventoryComponent != nullptr, TEXT("Target Character has not InventoryComponent"));
	TArray<FItemInstance>& ItemArray = InventoryComponent->GetItemArray();
	TArray<int32>& EquipmentSlot = InventoryComponent->GetEquipmentSlot();

	// Init EquipmentSlot
	
	for (int i = 0; i < EquipmentSlot.Num() - 2; ++i)
	{
		int32 TargetItemIndex = EquipmentSlot[i + 1];
		if (TargetItemIndex != -1)
		{
			FItem* ItemInfo = InventoryComponent->GetItemInfo(ItemArray[TargetItemIndex].ItemRow);
			EquipmentNameArray[i]->SetText(ItemInfo->ItemName);
		}
		else
		{
			EquipmentNameArray[i]->SetText(FText());
		}
	}
	
	// Init ItemList
	VB_ItemList->ClearChildren();

	checkf(InventoryItemListSlotClass != nullptr, TEXT("InventoryItemListSlotClass is not valid"));

	for (int i = 0; i < ItemArray.Num(); ++i)
	{
		UInventoryItemListSlot* InventoryItemListSlot = CreateWidget<UInventoryItemListSlot>(GetWorld()->GetFirstPlayerController(), InventoryItemListSlotClass);
		VB_ItemList->AddChildToVerticalBox(InventoryItemListSlot);

		if (ItemArray[i].ItemRow != "None")
		{
			FItem* Item = InventoryComponent->GetItemInfo(ItemArray[i].ItemRow);
			InventoryItemListSlot->InitWidget(Item, &ItemArray[i]);
		}
		InventoryItemListSlot->SetVisibility(ItemArray[i].bIsEquiped || ItemArray[i].ItemRow == "None" ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
	}
}