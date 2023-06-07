// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipSelectMenuWidget.generated.h"

/**
 * 
 */
class UButton;
class AMyCharacter;
UCLASS()
class VR12FORTHEKING_API UEquipSelectMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	void InitWidget(AMyCharacter* NewOwnerCharacter, int32 NewSlotIndex);
private:
	UFUNCTION()
	void UnequipButtonOnClicked();
	UFUNCTION()
	void CloseButtonOnClicked();
private:
	AMyCharacter* OwnerCharacter;
	int32 SlotIndex;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Unequip;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Hide;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Show;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Close;
};
