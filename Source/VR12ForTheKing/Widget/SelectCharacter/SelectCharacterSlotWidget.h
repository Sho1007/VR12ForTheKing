// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectCharacterSlotWidget.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;
class UVerticalBox;
class UEditableTextBox;
UCLASS()
class VR12FORTHEKING_API USelectCharacterSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void SetSlotIndex(int32 NewSlotIndex);
	FORCEINLINE void SetOwnerPlayerIndex(int32 NewOwnerPlayerIndex);

	void Select();
	void Selected();
	void Deselect();

	void Ready(bool bIsReady);

private:
	UFUNCTION()
	void SelectButtonOnClicked();
	UFUNCTION()
	void CancleButtonOnClicked();
	UFUNCTION()
	void ReadyButtonOnClicked();

private:
	int32 SlotIndex;
	int32 OwnerPlayerIndex;
private:
	// BindWidget
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Select;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Cancle;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Ready;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Color;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Class_Left;
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Class_Right;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UVerticalBox* VB_Customize;

	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UEditableTextBox* ETB_PlayerName;
	
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Ready;
};