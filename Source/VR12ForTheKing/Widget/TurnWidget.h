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
class UImage;
class UWidgetSwitcher;
class UTextBlock;
UCLASS()
class VR12FORTHEKING_API UTurnWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Get_Day_Text();

	UFUNCTION(BlueprintCallable)
	void ChaosCount();

	UFUNCTION(BlueprintCallable)
	void AddHeartCount();

	UFUNCTION(BlueprintCallable)
	void DeleteHeartCount();

	UFUNCTION(BlueprintCallable)
	void OpenSettion();

	UFUNCTION(BlueprintCallable)
	void TurnOver();

	UFUNCTION(BlueprintCallable)
	void ChangetoBattleTurnWidget();

	UFUNCTION(BlueprintCallable)
	void ChangetoMoveTurnWidget();

	void InitWidget();

	
private:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		UHeartSlot* HeartSlot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		TSubclassOf<UHeartSlot> HeartSlotClass;


	//widget
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UBattleTurnWidget* WBP_BattleTurnWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UMoveTurnWidget* WBP_MoveTurnWidget;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
	UWidgetSwitcher* MoveBattleSwitcher;

	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
	UHorizontalBox* HeartBox;

	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
	UImage* Chaos1;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
	UImage* Chaos2;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
	UImage* Chaos3;

	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* Day;
	
};
