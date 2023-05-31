// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/InventoryWidget.h"

#include "Components/VerticalBox.h"


#include "../Character/MyCharacter.h"
#include "../Component/InventoryComponent.h"

void UInventoryWidget::InitWidget(AMyCharacter* NewTargetCharacter)
{
	TargetCharacter = NewTargetCharacter;
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(TargetCharacter->GetComponentByClass(UInventoryComponent::StaticClass()));
	checkf(InventoryComponent != nullptr, TEXT("Target Character has not InventoryComponent"));


	// Init ItemList
	TArray<FItemInstance>& ItemArray = InventoryComponent->GetItemArray();

	for (int i = 0; i < ItemArray.Num(); ++i)
	{
		if (ItemArray[i].bIsEquiped) continue;

		//UInventoryItemListSlot* InventoryItemListSlot = CreateWidget<UInventoryItemListSlot>(GetWorld()->GetFirstPlayerController(), UInventoryItemListSlotClass);

		//VB_ItemList->AddChildToVerticalBox(InventoryItemListSlot);
	}
}