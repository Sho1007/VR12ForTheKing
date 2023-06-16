// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChanceCoinSlot.generated.h"


/**
 * 
 */
class UBorder;
class UTexture2D;
class UWidgetSwitcher;
UCLASS()
class VR12FORTHEKING_API UChanceCoinSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* CoinEmpty;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* CoinSuccess;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* CoinFail;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UWidgetSwitcher* ChanceCoinSwitcher;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	TArray<UTexture2D*> CoinImageArray;

	//Getter,Setter
	void SetImage(UTexture2D* NewImage);
	void SetSwitchCoinImage(int32 SwitcherIndex);
	UTexture2D* GetCoinImageFromArray(int32 CoinImageIndex);
};
