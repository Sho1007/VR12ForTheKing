// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipItemListSlot.generated.h"

/**
 * 
 */
struct FItem;

class UImage;
class UButton;
class UTextBlock;
class UTexture2D;

class AMyCharacter;
class UStatusWidget;
UCLASS()
class VR12FORTHEKING_API UEquipItemListSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetSlotIndex(UStatusWidget* NewStatusWidget, int32 NewSlotIndex);

	void InitWidget(AMyCharacter* NewOwnerCharacter);

private:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnClicked();
	UFUNCTION()
	void OnHovered();
	UFUNCTION()
	void OnUnhovered();

private:
	AMyCharacter* OwnerCharacter;
	UStatusWidget* StatusWidget;
	FItem* ItemInfo;
	int32 SlotIndex;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_EquipItem;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UImage* Img_EquipItemIcon;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_EquipItemName;

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = true))
	UTexture2D* SlotIcon;
};
