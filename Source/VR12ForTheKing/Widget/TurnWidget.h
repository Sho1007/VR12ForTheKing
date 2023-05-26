// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TurnWidget.generated.h"

/**
 * 
 */

class UMoveTurnWidget;
class UBattleTurnWidget;
class UHorizontalBox;
class UHeartSlot;
UCLASS()
class VR12FORTHEKING_API UTurnWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	FText Get_Day_Text();

	void ChaosCount();

	UFUNCTION(BlueprintCallable)
	void AddHeartCount();

	UFUNCTION(BlueprintCallable)
	void DeleteHeartCount();

	void OpenSettion();
	void TurnOver();
	void ChangetoBattleTurnWidget();
	void ChangetoMoveTurnWidget();

	

private:
	//widget
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UBattleTurnWidget* WBP_BattleTurnWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UMoveTurnWidget* WBP_MoveTurnWidget;

	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
	UHorizontalBox* HeartBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		UHeartSlot* HeartSlot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		TSubclassOf<UHeartSlot> HeartSlotClass;
};
