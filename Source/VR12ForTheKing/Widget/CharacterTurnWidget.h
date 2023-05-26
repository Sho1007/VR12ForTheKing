// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterTurnWidget.generated.h"

/**
 * 
 */
class UHorizontalBox;
UCLASS()
class VR12FORTHEKING_API UCharacterTurnWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void InitWidget();
	UFUNCTION(BlueprintCallable)
	bool IsEndDay();
	UFUNCTION(BlueprintCallable)
	bool UpdateWidget();
	UFUNCTION(BlueprintCallable)
	int32 GetDayCount()const;
private:
	UPROPERTY(BluePrintReadWrite,EditAnyWhere,meta=(AllowPrivateAccess = true))
	int32 DayCount;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true))
	int32 CurrentIndex;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true))
	bool bIsEndDay;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true))
	bool bIsNewDay;

	// widget var
	UPROPERTY(BluePrintReadWrite, EditAnyWhere, meta = (AllowPrivateAccess = true, BindWidget))
	UHorizontalBox* CharacterTurnBox;

};
