// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
class AMyCharacter;
class UVerticalBox;
class UInventoryItemListSlot;
class UTextBlock;
class UStatusWidget;
class UEquipItemListSlot;
UCLASS()
class VR12FORTHEKING_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitWidget(AMyCharacter* NewTargetCharacter);
	void SetParent(UStatusWidget* NewStatusWidget);
private:
	AMyCharacter* TargetCharacter;
	UStatusWidget* StatusWidget;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UVerticalBox* VB_ItemList;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UVerticalBox* VB_EquipmentSlot;
	
	TArray<UEquipItemListSlot*> EquipItemSlotArray;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UEquipItemListSlot* WBP_WeaponSlot;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UEquipItemListSlot* WBP_ShieldSlot;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UEquipItemListSlot* WBP_HeadgearSlot;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UEquipItemListSlot* WBP_ArmorSlot;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UEquipItemListSlot* WBP_FootwearSlot;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UEquipItemListSlot* WBP_NecklaceSlot;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UEquipItemListSlot* WBP_TrinketSlot;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UInventoryItemListSlot> InventoryItemListSlotClass;
};