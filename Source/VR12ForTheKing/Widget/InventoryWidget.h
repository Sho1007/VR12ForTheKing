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
UCLASS()
class VR12FORTHEKING_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
public:
	void InitWidget(UStatusWidget* StatusWidget, AMyCharacter* NewTargetCharacter);

private:
	AMyCharacter* TargetCharacter;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UVerticalBox* VB_ItemList;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UVerticalBox* VB_EquipmentSlot;
	
	TArray<UTextBlock*> EquipmentNameArray;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_WeaponSlotName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_ShieldSlotName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_HeadgearSlotName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_ArmorSlotName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_FootwearSlotName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_NecklaceSlotName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_TrinketSlotName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UInventoryItemListSlot> InventoryItemListSlotClass;
};
