// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSelectMenuWidget.generated.h"

/**
 * 
 */
class UButton;
class AMyCharacter;
UCLASS()
class VR12FORTHEKING_API UItemSelectMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	void InitWidget(AMyCharacter* NewOwnerCharacter, int32 NewItemIndex);

private:
	UFUNCTION()
	void CloseButtonOnClicked();
	UFUNCTION()
	void UseButtonOnClicked();
	UFUNCTION()
	void EquipButtonOnClicked();
private:
	AMyCharacter* OwnerCharacter;
	int32 ItemIndex;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Use;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Equip;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Sell;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Give1;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Give2;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Close;
};
