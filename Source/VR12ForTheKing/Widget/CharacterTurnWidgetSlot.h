// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterTurnWidgetSlot.generated.h"


/**
 * 
 */

class USizeBox;
class UImage;
UCLASS()
class VR12FORTHEKING_API UCharacterTurnWidgetSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BluePrintCallable)
	void SetSizeBig();
	UFUNCTION(BluePrintCallable)
	void SetSizeSmall();

private:
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true))
	float BaseSize;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true))
	float SizeModifier;

	//Widget Var
	UPROPERTY(BluePrintReadWrite,EditAnyWhere, meta=(AllowPrivateAccess=true,BindWidget))
	USizeBox* CharacterSizeBox;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
	UImage* CharacterImage;
};
