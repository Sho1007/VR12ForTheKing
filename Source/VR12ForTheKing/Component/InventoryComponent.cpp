// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/InventoryComponent.h"

#include "Engine/DataTable.h"
#include "Components/Image.h"

#include "../Component/StatusComponent.h"


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
	EquipmentSlot.Init(-1, (int32)EEquipmentType::SIZE);
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
		if (NewItemCount == 0)
		{
			return;
		}
		if (ItemArray[i].ItemRow == NewItemRow)
		{
			int32 EmptySpace = ItemArray[i].MaxStackCount - ItemArray[i].CurrentStackCount;
			if (EmptySpace > 0)
			{
				int32 AddItemCount = FMath::Min(NewItemCount, EmptySpace);
				// Todo : Add Effect
				ItemArray[i].CurrentStackCount += AddItemCount;
				NewItemCount -= AddItemCount;
				
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
		}
	}

	if (NewItemCount > 0)
	{
		// Todo : If Item Remain because Inventory is full
	}
}

int32 UInventoryComponent::GetCurrentGold() const
{
	return Gold;
}

void UInventoryComponent::AttachItemOption(EEquipmentType TargetEuipmentType)
{
	// Todo : Apply Item Effects

	FItem* Item = ItemDataTable->FindRow<FItem>(ItemArray[EquipmentSlot[(int32)TargetEuipmentType]].ItemRow, FString(""));
	checkf(Item != nullptr, TEXT("Cannot Find Item"));
	UStatusComponent* StatusComponent = Cast<UStatusComponent>(GetOwner()->GetComponentByClass(UStatusComponent::StaticClass()));
	checkf(Item != nullptr, TEXT("Character has not StatusComponent"));
	FCharacterStatus& CharacterStatus = StatusComponent->GetCharacterStatus();
	CharacterStatus.Armor		+= Item->BonusArmor;
	CharacterStatus.Cognition	+= Item->BonusCognition;
	CharacterStatus.Evasion		+= Item->BonusEvasion;
	CharacterStatus.Focus		+= Item->BonusFocus;
	CharacterStatus.Intelligence+= Item->BonusIntelligence;
	CharacterStatus.Luck		+= Item->BonusLuck;
	CharacterStatus.Resistance	+= Item->BonusResistance;
	CharacterStatus.Speed		+= Item->BonusSpeed;
	CharacterStatus.Strength	+= Item->BonusStrength;
	CharacterStatus.Talent		+= Item->BonusTalent;
	CharacterStatus.Vitality	+= Item->BonusVitality;
}

void UInventoryComponent::DetachItemOption(EEquipmentType TargetEuipmentType)
{
	FItem* Item = ItemDataTable->FindRow<FItem>(ItemArray[EquipmentSlot[(int32)TargetEuipmentType]].ItemRow, FString(""));
	checkf(Item != nullptr, TEXT("Cannot Find Item"));
	UStatusComponent* StatusComponent = Cast<UStatusComponent>(GetOwner()->GetComponentByClass(UStatusComponent::StaticClass()));
	checkf(Item != nullptr, TEXT("Character has not StatusComponent"));
	FCharacterStatus& CharacterStatus = StatusComponent->GetCharacterStatus();
	CharacterStatus.Armor			-= Item->BonusArmor;
	CharacterStatus.Cognition		-= Item->BonusCognition;
	CharacterStatus.Evasion			-= Item->BonusEvasion;
	CharacterStatus.Focus			-= Item->BonusFocus;
	CharacterStatus.Intelligence	-= Item->BonusIntelligence;
	CharacterStatus.Luck			-= Item->BonusLuck;
	CharacterStatus.Resistance		-= Item->BonusResistance;
	CharacterStatus.Speed			-= Item->BonusSpeed;
	CharacterStatus.Strength		-= Item->BonusStrength;
	CharacterStatus.Talent			-= Item->BonusTalent;
	CharacterStatus.Vitality		-= Item->BonusVitality;
}

bool UInventoryComponent::EquipItem(int ItemIndex)
{
	if (ItemIndex < 0 || ItemIndex >= ItemArray.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid ItemIndex"));
		return false;
	}
	FItemInstance& TargetItemInstance = ItemArray[ItemIndex];
	if (TargetItemInstance.ItemRow == FName("None"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Target InventorySlot is Empty"));
		return false;
	}
	FItem* TargetItemInfo = ItemDataTable->FindRow<FItem>(TargetItemInstance.ItemRow, FString(""));
	if (TargetItemInfo == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can not find Item at ItemRow"));
		return false;
	}
	if (TargetItemInstance.bIsEquiped)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target Item is already Equiped"));
		return false;
	}
	if (TargetItemInfo->ItemType != EItemType::EQUIPMENT)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target Item Type is not Equipment"));
		return false;
	}
	EEquipmentType TargetEquipmentType = TargetItemInfo->EquipmentType;

	UnEquipItem(TargetEquipmentType);

	TargetItemInstance.bIsEquiped = true;
	EquipmentSlot[(int32)TargetEquipmentType] = ItemIndex;

	AttachItemOption(TargetEquipmentType);
	// Todo : Update Inventory Widget;

	return true;
}

bool UInventoryComponent::UnEquipItem(EEquipmentType TargetSlot)
{
	int32 WornedEquipmentIndex = EquipmentSlot[(int32)TargetSlot];
	if (WornedEquipmentIndex == -1)
	{
		// Alreay Empty Slot
		return true;
	}

	DetachItemOption(TargetSlot);

	ItemArray[WornedEquipmentIndex].bIsEquiped = false;
	// Todo : Disapply Item Effects
	EquipmentSlot[(int32)TargetSlot] = -1;
	
	return true;
}