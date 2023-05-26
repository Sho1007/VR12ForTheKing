// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoveTurnWidget.generated.h"

/**
 * 
 */
class UCharacterTurnWidget;
class UHorizontalBox;
class UMoveTurnWidgetSlot;
UCLASS()
class VR12FORTHEKING_API UMoveTurnWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void MoveToNextDay(bool IsEndDay);
	UFUNCTION(BlueprintCallable)
	void InitTurnWidget(int32 StartTurnIndex = 1);
private:

	//widget
	UPROPERTY(BluePrintReadWrite,EditAnyWhere,meta =(AllowPrivateAccess = true, BindWidget))
	UCharacterTurnWidget* WBP_CharacterTurnWidget;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
	UHorizontalBox* MoveTurnBox;



	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true))
	int32 ChaosCount;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TSubclassOf<UMoveTurnWidgetSlot> MoveTurnWidgetSlotClass;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		UMoveTurnWidgetSlot* MoveTurnWidgetSlot;
};
