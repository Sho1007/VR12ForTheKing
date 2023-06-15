// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleWidget.generated.h"

/**
 *
 */
class AMyCharacter;
class UActionWidget;
class UHorizontalBox;
class UTextBlock;
class UBattleManagerComponent;
class UChanceCoinSlot;
UCLASS()
class VR12FORTHEKING_API UBattleWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void HideWidget();
	void ShowWidget();
	void InitWidget(AMyCharacter* NewTargetCharacter);
	void InitActionDiscription(FName NewActionName);
private:
	AMyCharacter* TargetCharacter;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TSubclassOf<UActionWidget> ActionWidgetClass;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TSubclassOf<UChanceCoinSlot> ChanceCoinSlotClass;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TArray<FText> ActionRangeTextArray;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TArray<FText> ActionTypeTextArray;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
		UHorizontalBox* HB_Action;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
		UHorizontalBox* CoinChanceBox;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* TB_ActionName;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* TB_ActionDiscription;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* TB_AttackRange;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* TB_AttackType;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* TB_Damage;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* TB_DamageType;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* TB_SlotAccuracy;
};
