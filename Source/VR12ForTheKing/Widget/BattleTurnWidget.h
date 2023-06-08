// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleTurnWidget.generated.h"

/**
 *
 */

class AMyCharacter;
class UBattleTurnWidgetSlot;
class UTexture2D;
class UHorizontalBox;
UCLASS()
class VR12FORTHEKING_API UBattleTurnWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void SetTurnArray(const TArray<AMyCharacter*>& NewTurnArray);

	UFUNCTION(BlueprintCallable)
		void InitBattleTurnWidget();

	UFUNCTION(BlueprintCallable)
		void MoveToNextTurn(AMyCharacter* NewCharacter = nullptr);

	UFUNCTION(BlueprintCallable)
		void RemoveUnitFromImageArray(int32 Index);

	UFUNCTION(BlueprintCallable)
		void AddUnitToImageArray(AMyCharacter* NewCharacter, int32 Index);
private:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TArray<AMyCharacter*> BasicTurnArray;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TSubclassOf<UBattleTurnWidgetSlot> BattleTurnWidgetSlotClass;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		UBattleTurnWidgetSlot* BattleTurnWidgetSlot;




	//widget
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
		UHorizontalBox* TurnImageArray;

};