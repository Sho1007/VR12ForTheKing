// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoveTurnWidgetSlot.generated.h"

/**
 * 
 */

class UBorder;
class UImage;
UCLASS()
class VR12FORTHEKING_API UMoveTurnWidgetSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	void InitWidgetIndex(int32 NewTurnIndex);

	bool IsChaos() const;
	int32 GetTurnIndex() const;

	void TurnOnChaos();
	void TurnOffChaos();
private:
	UPROPERTY(BluePrintReadWrite,EditAnyWhere,meta =(AllowPrivateAccess = true))
	bool bIsDay;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess=true))
	bool bIsChaos;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true))
	int32 TurnIndex;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true))
	int32 ChaosNum;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true))
	int32 ChaosIndex;
	UPROPERTY(BluePrintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	FLinearColor DayColor;
	UPROPERTY(BluePrintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	FLinearColor NightColor;

	// Widget Var
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* TurnBorder;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
	UImage* ChaosImage;

};

