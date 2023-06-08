// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/InventoryComponent.h"

#include "Engine/DataTable.h"
#include "Components/Image.h"

#include "../Component/StatusComponent.h"
#include "../Character/MyCharacter.h"

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
	EquipmentSlot.Init(FItemInstance(), (int32)EEquipmentType::SIZE);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(const FName NewItemRow, int32 NewItemCount)
{
	FItem* ItemInfo = ItemDataTable->FindRow<FItem>(NewItemRow, FString(""));
	if (ItemInfo == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Item Row"));
		return;
	}
	
	if (NewItemCount <= 0) return;
	for (int i = 0; i < ItemArray.Num(); ++i)
	{
		if (ItemArray[i].ItemRow == NewItemRow)
		{
			int32 EmptySpace = ItemArray[i].MaxStackCount - ItemArray[i].CurrentStackCount;
			int32 AddCount = FMath::Min(NewItemCount, EmptySpace);

			ItemArray[i].CurrentStackCount += AddCount;
			NewItemCount -= AddCount;

			if (NewItemCount == 0) break;
		}
	}

	while (NewItemCount > 0)
	{
		int32 AddCount = FMath::Min(ItemInfo->MaxStackCount, NewItemCount);
		NewItemCount -= AddCount;
		FItemInstance NewItem;
		NewItem.CurrentStackCount = AddCount;
		NewItem.ItemRow = NewItemRow;
		NewItem.MaxStackCount = ItemInfo->MaxStackCount;
		NewItem.bIsEquiped = false;
		ItemArray.Add(NewItem);
	}

	if (UpdateInventory.IsBound())
	{
		UpdateInventory.Execute();
	}
}

int32 UInventoryComponent::GetCurrentGold() const
{
	return Gold;
}

TArray<FItemInstance>& UInventoryComponent::GetItemArray()
{
	return ItemArray;
}

FItem* UInventoryComponent::GetItemInfo(FName NewItemRow)
{
	return ItemDataTable->FindRow<FItem>(NewItemRow, FString(""));
}

FItem* UInventoryComponent::GetItemInfoAtInventory(int32 ItemIndex)
{
	if (ItemIndex < 0 || ItemIndex >= ItemArray.Num()) nullptr;

	FName ItemRow = ItemArray[ItemIndex].ItemRow;

	return ItemDataTable->FindRow<FItem>(ItemRow, FString(""));
}

TArray<FItemInstance>& UInventoryComponent::GetEquipmentSlot()
{
	return EquipmentSlot;
}

void UInventoryComponent::AttachItemOption(EEquipmentType NewEquipmentType)
{
	// Todo : Apply Item Effects
	FItemInstance& ItemInstance = EquipmentSlot[(int32)NewEquipmentType];
	if (ItemInstance.ItemRow.IsNone()) return;

	FItem* Item = ItemDataTable->FindRow<FItem>(ItemInstance.ItemRow, FString(""));
	checkf(Item != nullptr, TEXT("Cannot Find Item"));
	UStatusComponent* StatusComponent = Cast<UStatusComponent>(GetOwner()->GetComponentByClass(UStatusComponent::StaticClass()));
	checkf(StatusComponent != nullptr, TEXT("Character has not StatusComponent"));

	// Todo : Update What is Changed Not All
	StatusComponent->SetArmor(StatusComponent->GetArmor() + Item->BonusArmor);
	StatusComponent->SetCognition(StatusComponent->GetCognition() + Item->BonusCognition);
	StatusComponent->SetEvasion(StatusComponent->GetEvasion() + Item->BonusEvasion);
	StatusComponent->SetMaxFocus(StatusComponent->GetMaxFocus() + Item->BonusMaxFocus);
	StatusComponent->SetIntelligence(StatusComponent->GetIntelligence() + Item->BonusIntelligence);
	StatusComponent->SetLuck(StatusComponent->GetLuck() + Item->BonusLuck);
	StatusComponent->SetResistance(StatusComponent->GetResistance() + Item->BonusResistance);
	StatusComponent->SetSpeed(StatusComponent->GetSpeed() + Item->BonusSpeed);
	StatusComponent->SetStrength(StatusComponent->GetStrength() + Item->BonusStrength);
	StatusComponent->SetTalent(StatusComponent->GetTalent() + Item->BonusTalent);
	StatusComponent->SetVitality(StatusComponent->GetVitality() + Item->BonusVitality);
}

void UInventoryComponent::DetachItemOption(EEquipmentType NewEquipmentType)
{
	FItemInstance& ItemInstance = EquipmentSlot[(int32)NewEquipmentType];
	if (ItemInstance.ItemRow.IsNone()) return;

	FItem* Item = ItemDataTable->FindRow<FItem>(ItemInstance.ItemRow, FString(""));
	checkf(Item != nullptr, TEXT("Cannot Find Item"));
	UStatusComponent* StatusComponent = Cast<UStatusComponent>(GetOwner()->GetComponentByClass(UStatusComponent::StaticClass()));
	checkf(StatusComponent != nullptr, TEXT("Character has not StatusComponent"));

	// Todo : Update What is Changed Not All
	StatusComponent->SetArmor(StatusComponent->GetArmor() - Item->BonusArmor);
	StatusComponent->SetCognition(StatusComponent->GetCognition() - Item->BonusCognition);
	StatusComponent->SetEvasion(StatusComponent->GetEvasion() - Item->BonusEvasion);
	StatusComponent->SetMaxFocus(StatusComponent->GetMaxFocus() - Item->BonusMaxFocus);
	StatusComponent->SetIntelligence(StatusComponent->GetIntelligence() - Item->BonusIntelligence);
	StatusComponent->SetLuck(StatusComponent->GetLuck() - Item->BonusLuck);
	StatusComponent->SetResistance(StatusComponent->GetResistance() - Item->BonusResistance);
	StatusComponent->SetSpeed(StatusComponent->GetSpeed() - Item->BonusSpeed);
	StatusComponent->SetStrength(StatusComponent->GetStrength() - Item->BonusStrength);
	StatusComponent->SetTalent(StatusComponent->GetTalent() - Item->BonusTalent);
	StatusComponent->SetVitality(StatusComponent->GetVitality() - Item->BonusVitality);
}

bool UInventoryComponent::EquipItem(int32 ItemIndex)
{
	if (ItemIndex < 0 || ItemIndex >= ItemArray.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid ItemIndex"));
		return false;
	}
	FItemInstance& ItemInstance = ItemArray[ItemIndex];
	FItem* ItemInfo = ItemDataTable->FindRow<FItem>(ItemInstance.ItemRow, FString(""));
	if (ItemInfo == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can not find Item at ItemRow"));
		return false;
	}
	if (ItemInstance.bIsEquiped)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target Item is already Equiped"));
		return false;
	}
	if (ItemInfo->ItemType != EItemType::EQUIPMENT)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target Item Type is not Equipment"));
		return false;
	}
	EEquipmentType EquipmentType = ItemInfo->EquipmentType;

	UnEquipItem(EquipmentType);

	ItemInstance.bIsEquiped = true;
	EquipmentSlot[(int32)EquipmentType] = ItemInstance;
	ItemArray.RemoveAt(ItemIndex);

	AttachItemOption(EquipmentType);
	// Todo : Update Inventory Widget;

	if (UpdateInventory.IsBound())
	{
		UpdateInventory.Execute();
	}

	return true;
}

bool UInventoryComponent::UnEquipItem(EEquipmentType TargetSlot)
{
	FItemInstance& ItemInstance = EquipmentSlot[(int32)TargetSlot];
	if (ItemInstance.ItemRow.IsNone())
	{
		// Alreay Empty Slot
		UE_LOG(LogTemp, Warning, TEXT("Slot is Already None"));
		return true;
	}

	DetachItemOption(TargetSlot);

	ItemInstance.bIsEquiped = false;

	ItemArray.Add(ItemInstance);

	// Todo : Disapply Item Effects
	EquipmentSlot[(int32)TargetSlot].ItemRow = FName("None");

	if (UpdateInventory.IsBound())
	{
		UpdateInventory.Execute();
	}
	
	return true;
}

bool UInventoryComponent::UseItem(int32 ItemIndex)
{
	FItemInstance& ItemInstance = ItemArray[ItemIndex];
	FItem* ItemInfo = GetItemInfoAtInventory(ItemIndex);
	if (ItemInfo == nullptr) return false;

	
	AMyCharacter* OwnerCharacter = Cast<AMyCharacter>(GetOwner());

	AItemBase* ItemBase = GetWorld()->SpawnActor<AItemBase>(ItemInfo->ItemClass, FVector(0, 0, 0), FRotator(0, 0, 0));
	checkf(ItemBase != nullptr, TEXT("ItemBase is not Spawned"));

	UE_LOG(LogTemp, Warning, TEXT("ItemBase Spawned"));
	ItemBase->Use(OwnerCharacter);
	
	if (--ItemInstance.CurrentStackCount == 0)
	{
		ItemArray.RemoveAt(ItemIndex);
	}

	if (UpdateInventory.IsBound())
	{
		UpdateInventory.Execute();
	}

	return false;
}