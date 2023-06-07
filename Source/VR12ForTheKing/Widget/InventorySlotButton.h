// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "InventorySlotButton.generated.h"

/**
 * 
 */
struct FItem;
struct FItemInstance;

class AMyCharacter;
class UInventoryComponent;
class UStatusWidget;
UCLASS()
class VR12FORTHEKING_API UInventorySlotButton : public UButton
{
	GENERATED_BODY()
	
public:
	void NativeConstruct(UStatusWidget* NewStatusWidget);

	void InitWidget(UInventoryComponent* NewOwnerInventory, int32 NewItemIndex);
private:
	UStatusWidget* StatusWidget;

	UInventoryComponent* OwnerInventory;
	int32 ItemIndex;

	UFUNCTION()
	void ButtonOnHovered();
	UFUNCTION()
	void ButtonOnUnhovered();
	UFUNCTION()
	void ButtonOnClicked();
};
