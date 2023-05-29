// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/InventoryComponent.h"

#include "Engine/DataTable.h"

#include "Components/Image.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	checkf(ItemDataTable != nullptr, TEXT("ItemDataTable is not valid"));
	ItemArray.Init(FItemInstance(), 10);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(const FName NewItemRow, int32 NewItemCount)
{
	// Todo : Change ReturnType to int32? present remain item count 
	for (int i = 0; i < ItemArray.Num(); ++i)
	{
		if (ItemArray[i].ItemRow == NewItemRow)
		{
			int32 EmptySpace = ItemArray[i].MaxStackCount - ItemArray[i].CurrentStackCount;
			if (EmptySpace > 0)
			{
				int32 AddItemCount = FMath::Min(NewItemCount, EmptySpace);
				// Todo : Add Effect
				ItemArray[i].CurrentStackCount += AddItemCount;
				NewItemCount -= AddItemCount;
				if (NewItemCount == 0)
				{
					return;
				}
			}
		}
		else if (ItemArray[i].ItemRow == FName(TEXT("None")))
		{
			FItem* ItemRow = ItemDataTable->FindRow<FItem>(NewItemRow, FString(""));
			if (ItemRow == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("Can't Find Item"));
				return;
			}
			ItemArray[i].ItemRow = NewItemRow;
			int32 AddItemCount = FMath::Min(NewItemCount, ItemRow->MaxStackCount);
			ItemArray[i].CurrentStackCount = AddItemCount;
			ItemArray[i].MaxStackCount = ItemRow->MaxStackCount;
			NewItemCount -= AddItemCount;
			if (NewItemCount == 0)
			{
				return;
			}
		}
	}

	if (NewItemCount > 0)
	{
		// Todo : If Item Remain because Inventory is full
	}
}