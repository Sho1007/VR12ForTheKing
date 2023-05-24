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
	bool IsChaos() const;


	UFUNCTION(BlueprintCallable)
	void InitWidgetIndex();

	void TurnOnChaos(int32 NewChaosIndex);

private:
	UPROPERTY(BluePrintReadWrite,EditAnyWhere,meta =(AllowPrivateAccess = true))
	bool bIsDay;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess=true))
	bool bIsChaos;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true))
	int32 CurrentTurnIndex;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true))
	int32 NewChaosNum;
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

