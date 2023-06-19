// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/InventoryWidget.h"

#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"


#include "../Character/MyCharacter.h"
#include "../Component/InventoryComponent.h"
#include "../Widget/InventoryItemListSlot.h"
#include "EquipItemListSlot.h"

void UInventoryWidget::InitWidget(AMyCharacter* NewTargetCharacter)
{
	TargetCharacter = NewTargetCharacter;
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(TargetCharacter->GetComponentByClass(UInventoryComponent::StaticClass()));
	checkf(InventoryComponent != nullptr, TEXT("Target Character has not InventoryComponent"));
	TArray<FItemInstance>& ItemArray = InventoryComponent->GetItemArray();
	TArray<FItemInstance>& EquipmentSlot = InventoryComponent->GetEquipmentSlot();

	// Init EquipmentSlot

	for (int i = 0; i < EquipItemSlotArray.Num(); ++i)
	{
		EquipItemSlotArray[i]->InitWidget(TargetCharacter);
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

void UInventoryWidget::SetParent(UStatusWidget* NewStatusWidget)
{
	StatusWidget = NewStatusWidget;

	int32 ChildrenCount = VB_EquipmentSlot->GetChildrenCount();
	for (int i = 0; i < ChildrenCount; ++i)
	{
		EquipItemSlotArray.Add(Cast<UEquipItemListSlot>(VB_EquipmentSlot->GetChildAt(i)));
		EquipItemSlotArray[i]->SetSlotIndex(StatusWidget, i + 1);
	}


}