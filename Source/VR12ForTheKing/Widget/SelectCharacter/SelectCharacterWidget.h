// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectCharacterWidget.generated.h"

/**
 * 
 */
struct FPlayerData;
class USelectCharacterSlotWidget;
UCLASS()
class VR12FORTHEKING_API USelectCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void UpdateWidget(TArray<FPlayerData>& PlayerDataArray);

private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	USelectCharacterSlotWidget* WBP_SelectCharacterSlot1;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	USelectCharacterSlotWidget* WBP_SelectCharacterSlot2;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	USelectCharacterSlotWidget* WBP_SelectCharacterSlot3;

	TArray<USelectCharacterSlotWidget*> SelectCharacterSlotArray;
};
