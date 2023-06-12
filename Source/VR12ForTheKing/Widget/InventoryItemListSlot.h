// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemListSlot.generated.h"

/**
 * 
 */
struct FItem;

class UTextBlock;
class UImage;
class UButton;
class AMyCharacter;
class UStatusWidget;
UCLASS()
class VR12FORTHEKING_API UInventoryItemListSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitWidget(UStatusWidget* NewStatusWidget, AMyCharacter* NewOwnerCharacter, int32 NewItemIndex);
private:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void ButtonOnClicked();
	UFUNCTION()
	void ButtonOnHovered();
	UFUNCTION()
	void ButtonOnUnhovered();
private:
	UStatusWidget* StatusWidget;
	AMyCharacter* OwnerCharacter;
	int32 ItemIndex;
	FItem* ItemInfo;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Item;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_ItemName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_ItemCount;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UImage* Img_ItemIcon;
};
